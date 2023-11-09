#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace std {

    vector<int> compress(string data) {
        unordered_map<string, int> dictionary;  // Инициализация словаря
        int current_code = 256;  // Начальный код для новых последовательностей

        vector<int> result;  // Вектор для хранения сжатых кодов
        string buffer = "";  // Буфер для накопления символов

        for (char c : data) {
            buffer += c;  // Добавляем символ к текущей последовательности
            if (dictionary.find(buffer) == dictionary.end()) {  // Если такая последовательность отсутствует в словаре
                dictionary[buffer] = current_code;  // Добавляем её в словарь
                current_code++;  // Увеличиваем текущий код

                // Записываем код для предыдущей последовательности в результат
                result.push_back(dictionary[buffer.substr(0, buffer.size()-1)]);

                buffer = c;  // Начинаем новую последовательность с текущего символа
            }
        }

        if (dictionary.find(buffer) != dictionary.end()) {
            result.push_back(dictionary[buffer]);
        }

        return result;
    }

    string decompress(vector<int> compressed_data) {
        unordered_map<int, string> dictionary;  // Инициализация словаря
        int current_code = 256;  // Начальный код для новых последовательностей

        string result = "";  // Строка для хранения распакованных символов
        int prev_code = compressed_data[0];  // Получаем первый код из сжатых данных
        result += static_cast<char>(prev_code);  // Добавляем соответствующий символ в результат

        for (size_t i = 1; i < compressed_data.size(); ++i) {
            int code = compressed_data[i];
            string entry;

            if (dictionary.find(code) != dictionary.end()) {  // Если код уже есть в словаре
                entry = dictionary[code];  // Получаем соответствующую последовательность
            } else if (code == current_code) {  // Если код соответствует новой последовательности
                entry = dictionary[prev_code] + dictionary[prev_code][0];  // Формируем новую последовательность
            } else {
                throw runtime_error("Некорректные данные сжатия");
            }

            result += entry;  // Добавляем последовательность в результат
            dictionary[current_code] = dictionary[prev_code] + entry[0];  // Добавляем новую последовательность в словарь
            current_code++;  // Увеличиваем текущий код
            prev_code = code;  // Обновляем предыдущий код
        }

        return result;
    }

}  // namespace std

int main() {
    using namespace std;  // Используем пространство имен std

    string original_data = "ABABABA";
    vector<int> compressed_data = compress(original_data);
    cout << "Сжатые данные: ";
    for (int code : compressed_data) {
        cout << code << " ";
    }
    cout << endl;

    string decompressed_data = decompress(compressed_data);
    cout << "Распакованные данные: " << decompressed_data << endl;

    return 0;
}
