	
#include <stdlib.h>
#include <locale.h>

int ft_printf(const char *format, ...);
char *setlocal(int categorie, const char *locale);
int main()
{
	int i= 1;
	char *l = setlocale(LC_ALL,"en_US.UTF-8");
	printf("\nret %d\n", printf("%5.2s is a string", "this"));
  	printf("\nft ret %d\n", ft_printf("%5.2s is a string", "this"));
	return (0);
}
