#include "bst.cpp"
#include "control.cpp"
#include "hashtable.cpp"
#include "randtree.cpp"
#include "timer.cpp"
using namespace std;

const string BIN_FILENAME = ".bin";
const string TXT_FILENAME = ".city";
int main() {
    convert_text_to_binary(TXT_FILENAME, BIN_FILENAME);
    Control control (BIN_FILENAME, new BSTree) ;
    for (int i = 0; i < 10; i++) {
        control.add_from_bin(i);
    }
    control.print_map();
    return 0;
}
