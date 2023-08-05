#include <stdio.h>
#include <string.h>
#include <ctype.h>
// g_ means global variable

struct AnswerDicInfo
{
    char secret_phrases[ 50 ] ;
}answer_dics[ 52 ] ;
char g_pattern[ 500 ] ;
int g_key_index[ 55 ] ;
int g_num_key_index = 0  ;
int g_lps[ 500 ] ;
int g_sum_lps = 0 ;

void ProcessInput( char* ciphertext , char* article ) ;
void CalculateLps(char* pat, int lenp ) ; // FailureArray Implementation
void PatternMatch(char* pat, char* txt) ;
void FindKeyByROT( char* ciphertext  ) ;
int MyChangingFunction( int key_index_value ) ;// To change ascii to index ;
void PrintAnswerDic( int index_of_answer_dic ) ;
void PrintFinalAnswer( char* ciphertext , int sum_lps ) ;

int main()
{
    char txt[ 500 ] ; // ciphertext
    char article[ 500 ] ;
    ProcessInput( txt , article ) ;
    FindKeyByROT( txt ) ;
    PatternMatch( g_pattern , article);
    PrintFinalAnswer( txt , g_sum_lps ) ;
    return 0;
}

void PatternMatch(char* pat, char* txt) // KMP Implementation
{
    int i = 0; // i 代表 article 目前的位置
    int j = 0; // j 代表 所尋找 pattern 目前位置
    int lenp = strlen(pat);
    int lent= strlen(txt);

    CalculateLps(  pat  , lenp );

    while (i < lent) // 一直找文章到結束為止
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == lenp ) //找到了 ， 開陣列記錄起來 。
        {
            g_key_index[ g_num_key_index ] = i - j ;
            g_num_key_index++ ;
            j = g_lps[j - 1];
        }
        else if (i < lent && pat[j] != txt[i]) //沒找到 ， 做smart shift
        {
            if (j != 0)
            {
                 j = g_lps[ j - 1 ] ;
            }
            else
            {
                 i = i + 1 ;
            }
        }
    }
}


void CalculateLps(char* pat, int lenp) // FailureArray Implementation
{
    int len = 0; // 就是k 要盡量找最大
    g_lps[0] = 0; // 這邊用0 ， 也可以用-1
    int i = 1;
    while (i < lenp) // 從 i = 1 找到 lenp - 1
    {
        if (pat[i] == pat[len])
        {
            len++;
            g_lps[i] = len;
            i++;
        }
        else
        {
            if (  len != 0  ) // 對應不到就把k變小往前找
            {
                len = g_lps[len - 1];
            }
            else
            {
                g_lps[i] = 0;
                i++;
            }
        }
    }
    //k : f(j) = largest k < j such that p0p1...pk = pj-k...pj
   //  if such a k >= 0  exsists , otherwise f(j) = 0
}
void FindKeyByROT( char* ciphertext  ) // ROT  Implementation
{
    int lenc = strlen( ciphertext ) ;
    for( int i = 0 ; i < lenc  ; i++ )
    {
        int origin_text = ( int ) ciphertext[ i ] ;
        origin_text  -= 13 ;
        if( origin_text < 97 && islower( ciphertext[ i  ] ) )
        {
            origin_text = 123 - ( 97 - origin_text ) ;
            ciphertext[ i ] = ( char ) origin_text ;
        }
        else if( origin_text < 65 && isupper( ciphertext[  i  ] ) )
        {
            origin_text = 91 - ( 65 - origin_text ) ;
            ciphertext[ i ] = ( char ) origin_text ;
        }
        else
        {
            ciphertext[ i ] = ( char ) origin_text ;
        }
    }
    for( int i = 0 ; i < 5 ; i++ )
    {
        g_pattern[ i ] = ciphertext[ i ] ;
    }
}

int MyChangingFunction( int key_index_value ) // ChangeValueToAnswerDicIndex
{
    int index_answer_dic = -1 ;
    if( key_index_value >= 65 && key_index_value <= 90 )
    {
        index_answer_dic = key_index_value-65 ;
    }
    else
    {
        index_answer_dic = key_index_value - 97 +26 ;
    }
    return index_answer_dic ;
}

void PrintAnswerDic( int index_answer_dic ) // print out answer dic
{
    int lenth =strlen( answer_dics[ index_answer_dic ].secret_phrases ) ;
    for( int i = 2 ; i < lenth  ; i++ )
    {
        printf("%c",answer_dics[ index_answer_dic ].secret_phrases[ i ] ) ;
    }
}

void PrintFinalAnswer( char* ciphertext , int sum_lps )
{
    printf("%s\n", ciphertext) ;
    printf("%s\n", g_pattern) ;
    for( int i = 0 ; i < 5 ; i++ )
    {
        sum_lps += g_lps[ i ] ;
    }
    printf("%d\n", sum_lps ) ;
    for( int i = 0 ; i < g_num_key_index ; i++ )
    {
        g_key_index[ i ] += sum_lps ;
        printf("%d\n",g_key_index[ i ] ) ;
    }
    for( int i = 0 ; i < g_num_key_index ; i++ )
    {
       int index_answer_dic = g_key_index[ i ] ;
       index_answer_dic = MyChangingFunction( index_answer_dic ) ;
       PrintAnswerDic( index_answer_dic ) ;
       printf(" ") ;
    }
}

void ProcessInput( char* ciphertext , char* article )
{
    fgets( ciphertext , 500 , stdin ) ;
    fgets( article , 500 , stdin ) ;
    for( int i = 0 ; i < 52 ; i++ )
    {
        fgets( answer_dics[ i ].secret_phrases , 50 , stdin ) ;
        int len_dic = strlen( answer_dics[ i ].secret_phrases )  ;
        answer_dics[ i ].secret_phrases[ len_dic - 1 ] = '\0' ;
    } // put answer dic in struct
    int lena = strlen( article ) , lent = strlen( ciphertext ) ; // lenth_of_string
    article[ lena - 1 ] = '\0' ;
    ciphertext[ lent - 1 ] = '\0' ;
}
