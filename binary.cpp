#include "binary.h"
using namespace std;

Record::Record(int city_code, string city_name) {
    this->city_code = city_code;
    this->city_name = city_name;
}

Record::Record() {
    city_code = 0;
    city_name = "undefined";
}

int hash_string(string str) {
    int hash = 7;
    for (int i = 0; i < str.length(); i++)
        hash = 13 * hash + str[i];
    return hash;
}

void Record::print() {
    printf("<Record name=%s code=%d>\n", city_name.c_str(), city_code);
}

void write_binary_file(string filename, Record *records, int n) {
    ofstream file(filename, ios::binary | ios::trunc);
    file.write((char *)&n, sizeof(int));
    file.write((char *)records, n * sizeof(Record));
    file.close();
}

Record *read_binary_file(string filename, int &n) {
    ifstream file(filename, ios::in | ios::binary);
    file.read((char *)&n, sizeof(int));
    Record *records = new Record[n];
    file.read((char *)records, n * sizeof(Record));
    file.close();
    return records;
}

void write_text_file(string filename, Record *records, int n) {
    ofstream file(filename);
    file << n << endl;
    for (int i = 0; i < n; i++) {
        Record r = records[i];
        file << r.city_name << " " << r.city_code << endl;
    }
    file.close();
}

Record *read_text_file(string filename, int &n) {
    ifstream file(filename);
    file >> n;
    Record *records = new Record[n];
    for (int i = 0; i < n; i++)
        file >> records[i].city_name >> records[i].city_code;
    file.close();
    return records;
}

void convert_text_to_binary(string infilename, string outfilename) {
    int n;
    Record *records = read_text_file(infilename, n);
    write_binary_file(outfilename, records, n);
}

void convert_binary_to_text(string infilename, string outfilename) {
    int n;
    Record *records = read_binary_file(infilename, n);
    write_text_file(outfilename, records, n);
}

Record find_in_binary_file_by_index(string filename, int index) {
    Record record;
    ifstream file(filename, ios::in | ios::binary);
    file.seekg(index * sizeof(Record) + sizeof(int), ios::beg);
    file.read((char *)&record, sizeof(Record));
    file.close();
    return record;
}

void delete_by_index_in_binary_file(string filename, int index) {
    fstream file(filename, ios::out | ios::in | ios::binary);
    int n;
    file.read((char *)&n, sizeof(int));
    if (index == n - 1) {
        file.close();
        return;
    }

    Record last_record = find_in_binary_file_by_index(filename, n - 1);
    file.seekg(sizeof(Record) * index, ios::cur);
    file.write((char *)&last_record, sizeof(Record));

    n -= 1;
    file.seekg(0, ios::beg);
    file.write((char *)&n, sizeof(int));
    file.close();
    return;
}
