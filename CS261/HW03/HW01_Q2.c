void HW03(long int x, long int y, long int* z) {
    unsigned long int result = x;

    switch(y) {
        case 13: 
            result = result + 13;
            break;
        case 15: 
            result = (((result * 4) * 2) + (2 * result));
        case 16: 
            result = result + 5;
            break;
        case 18: 
            result = result << 1;
            break;
        case 20: 
            result = result << 3;
            break;
        default: 
            result = 0;
    }

    *z = result;
    }

int main() {
    return 0;
}
