#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}


char	*ft_trim(char	*s1)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] && (s1[i] == 32 || s1[i] == 9)) // vertical tab => 9
		i++;
	while (s1[len] && (s1[len] == 32 || s1[len] == 9))
		len--;
    s1[len + 1] = '\0';
	return (s1 + i);
}

int main() {
    char input[] = "   Bu bir örnek cüml edir.   ";

    // Boşlukları kaldır
    char *trimmed = ft_trim(input);

    // Sonucu yazdır
    printf("Dizeden önce: \"%s\"\n", input);
    printf("Dizeden sonra: \"%s\"\n", trimmed);

    system("leaks a.out");
    return 0;
}