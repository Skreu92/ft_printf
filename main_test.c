	
#include <stdlib.h>

int ft_printf(const char * format, ...);
int main()
{
	printf("retour %d\n" , printf("coucou %d %s", 42));
	printf("ft retour %d\n" , ft_printf("%d %s", 42, "yoyoyoyo"));
	return (0);
}
