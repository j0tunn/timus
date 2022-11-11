#include <iostream>

int main()
{
    unsigned int n, k;

    std::cin >> n >> k;

    // можно пожарить с одной стороны все, потом отложить часть пожаренных с одной стороны, и положить оставшиеся
    // (это будет раоботать, если оставшихся не больше половины сковороды)
    // так же стоит учесть, что минимум 2 минуты точно понадобится
    std::cout << ( n > k ? (n/k * 2 + (n%k == 0 ? 0 : n%k > k/2 ? 2 : 1) ) : 2 ) << std::endl;

    return 0;
}
