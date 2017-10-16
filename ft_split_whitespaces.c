#include <stdlib.h>

int     ft_is_space(char p_c)
{
        if ((p_c == ' ') || (p_c == '\t') || (p_c == '\n'))
            return (1);

        else
            return (0);
}

/*
** count the number of words in str
*/
int     get_nb_words(char *str)
{
        int     count;
        int     ret_nb_words;
        int     bool_iw;        /* are we in a word */

        count = 0;
        ret_nb_words = 0;
        bool_iw = 0;

        /* we parse str */
        while (str[count] != '\0')
        {
            /* if we enter in a word */
            if ((!ft_is_space(str[count])) && !bool_iw)
            {
                bool_iw = 1;
                ret_nb_words++;
            }

            /* if we go out of a word */
            if ((ft_is_space(str[count])) && bool_iw)
                bool_iw = 0;

            count++;
        }

        return (ret_nb_words);
}

/*
** return the index  of the first char of the first word found in str,
** by starting the parsing at p_index
** and stock the size of the word in *ptr_val (rem: "fc" = First Char)
*/
int     get_fcword_n_putsize(char *str, int p_index, int* ptr_to_val)
{
        int     bool_iw;    /* are we in a word */
        int     beg;

        beg = 0;
        bool_iw = 0;

        /* we parse str starting at p_index */
        while (str[p_index] != '\0')
        {
            /* if we enter in a word */
            if ((!ft_is_space(str[p_index])) && !bool_iw)
            {
                /* we save the location of the begining of the word */
                beg = p_index;
                bool_iw = 1;

                /* while we are still in the word */
                while (!ft_is_space(str[p_index]))
                    p_index++;

                /* put the size of the word without \0 */
                *ptr_to_val = (p_index - beg);
                break ;
            }

            p_index++;
        }

        return (beg);
}
char    **ft_split_whitespaces(char *str)
{
    int     count1;
    int     count2;
    int     count3;
    int     temp_size_word;
    char    **ret_array;

    /* allow ret_array[nb_words] */
    count1 = 0;
    count2 = 0;
    ret_array = (char**)malloc(sizeof(char*) * (get_nb_words(str) + 1));

    /* allow ret_array[nb_words][size_word] */
    while (count1 < get_nb_words(str))
    {
        /*
        ** get the location of the first word found starting at str[count2], 
        ** get and put its size in temp_size_word and allow ret_array[count1]
        */
        count2 = get_fcword_n_putsize(str, count2, &temp_size_word);
        ret_array[count1] = (char*)malloc(sizeof(char) * (temp_size_word + 1));

        /* copy the word found in ret_array[count1] */
        count3 = 0;
        while (count3 < temp_size_word)
        {
            ret_array[count1][count3] = str[count2];
            count2++;
            count3++;
        }

        ret_array[count1][count3] = '\0';
        count1++;
    }

    /* final 0 to know that it's the end of the array */
    ret_array[get_nb_words(str)] = (char*)(malloc(sizeof (char)));
    *ret_array[get_nb_words(str)] = 0;
    return (ret_array);
}
