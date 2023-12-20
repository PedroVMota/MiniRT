#include <center.h>

int	ft_sep_validator(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_num_sub(char *str, char *charset)
{
	int	words;
	int	index;

	index = 0;
	words = 0;
	while (str[index])
	{
		if (ft_sep_validator(str[index], charset) && str[index])
		{
			index++;
			continue ;
		}
		words++;
		while (!(ft_sep_validator(str[index], charset)) && str[index])
			index++;
	}
	return (words);
}

void	ft_write_content(char *split, char *current_position, int size)
{
	int	index;

	index = 0;
	while (index < size - 1)
	{
		split[index] = current_position[index];
			index++;
	}
	split[index] = 0;
}

void	ft_strings_content(char **splitted, char *str, char *charset)
{
	int	i;
	int	malloc_index;
	int	word_beginning_index;

	i = 0;
	malloc_index = 0;
	while (str[i])
	{
		if (ft_sep_validator(str[i], charset))
		{
			i++ ;
			continue ;
		}
		word_beginning_index = i;
		while (!ft_sep_validator(str[i], charset) && str[i])
			i++;
		splitted[malloc_index] = malloc(sizeof(char)
				* (i - word_beginning_index + 1));
		ft_write_content(splitted[malloc_index], str + word_beginning_index,
			(i - word_beginning_index + 1));
		malloc_index++;
	}
}

char	**ft_splitstr(char *str, char *charset)
{
	int		n_sub_str;
	char	**split;

	if (*charset == 0)
		split = malloc(sizeof(char *) * 2);
	n_sub_str = ft_num_sub(str, charset);
	split = malloc((n_sub_str + 1) * sizeof(char *));
	if (!split)
		return (0);
	split[n_sub_str] = 0;
	ft_strings_content(split, str, charset);
	return (split);
}


//this is just the split from pescine 