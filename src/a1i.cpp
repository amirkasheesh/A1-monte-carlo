#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include <iomanip>
#include <string>


int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t N = 3000000;
    std::string size_rect = "narrow";
    uint64_t seed = 123456;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--rect" && i + 1 < argc) {
            size_rect = argv[++i];
        } else if (a == "--N" && i + 1 < argc) {
            N = std::stoll(argv[++i]);
        } else if (a == "--seed" && i + 1 < argc) {
            seed = std::stoull(argv[++i]);
        }
    }

    if (size_rect != "narrow" && size_rect != "wide") {
        std::cerr << "rect must be narrow|wide\n";
        return 1;
    }

    std::vector<std::tuple<double, double, double>> input_data(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> std::get<0>(input_data[i]) >> std::get<1>(input_data[i]) >> std::get<2>(input_data[i]);
    }

    double L;
    double R;
    double T;
    double B;
    if (size_rect == "narrow") {
        // Найдем левую границу по x
        double left_border_by_x = std::max({
            std::get<0>(input_data[0]) - std::get<2>(input_data[0]),  // x_1 - r_1
            std::get<0>(input_data[1]) - std::get<2>(input_data[1]),  // x_2 - r_2
            std::get<0>(input_data[2]) - std::get<2>(input_data[2])   // x_3 - r_3
        });

        // Найдем правую границу по x
        double right_border_by_x = std::min({
            std::get<0>(input_data[0]) + std::get<2>(input_data[0]),  // x_1 + r_1
            std::get<0>(input_data[1]) + std::get<2>(input_data[1]),  // x_2 + r_2
            std::get<0>(input_data[2]) + std::get<2>(input_data[2])   // x_3 + r_3
        });

        // Найдем нижнюю границу по y
        double bottom_border_by_y = std::max({
            std::get<1>(input_data[0]) - std::get<2>(input_data[0]),  // y_1 - r_1
            std::get<1>(input_data[1]) - std::get<2>(input_data[1]),  // y_2 - r_2
            std::get<1>(input_data[2]) - std::get<2>(input_data[2])   // y_3 - r_3
        });

        // Найдем верхнюю границу по y
        double top_border_by_y = std::min({
            std::get<1>(input_data[0]) + std::get<2>(input_data[0]),  // y_1 + r_1
            std::get<1>(input_data[1]) + std::get<2>(input_data[1]),  // y_2 + r_2
            std::get<1>(input_data[2]) + std::get<2>(input_data[2])   // y_3 + r_3
        });

        if (left_border_by_x >= right_border_by_x || bottom_border_by_y >= top_border_by_y) {
            std::cout << std::fixed << std::setprecision(10) << 0.0 << '\n';
            return 0;  // Общего пересечения кругов нет
        }
        L = left_border_by_x;
        R = right_border_by_x;
        T = top_border_by_y;
        B = bottom_border_by_y;
    } else if (size_rect == "wide") {
        // Найдем левую границу по x
        double left_border_by_x = std::min({
            std::get<0>(input_data[0]) - std::get<2>(input_data[0]),  // x_1 - r_1
            std::get<0>(input_data[1]) - std::get<2>(input_data[1]),  // x_2 - r_2
            std::get<0>(input_data[2]) - std::get<2>(input_data[2])   // x_3 - r_3
        });

        // Найдем правую границу по x
        double right_border_by_x = std::max({
            std::get<0>(input_data[0]) + std::get<2>(input_data[0]),  // x_1 + r_1
            std::get<0>(input_data[1]) + std::get<2>(input_data[1]),  // x_2 + r_2
            std::get<0>(input_data[2]) + std::get<2>(input_data[2])   // x_3 + r_3
        });

        // Найдем нижнюю границу по y
        double bottom_border_by_y = std::min({
            std::get<1>(input_data[0]) - std::get<2>(input_data[0]),  // y_1 - r_1
            std::get<1>(input_data[1]) - std::get<2>(input_data[1]),  // y_2 - r_2
            std::get<1>(input_data[2]) - std::get<2>(input_data[2])   // y_3 - r_3
        });

        // Найдем верхнюю границу по y
        double top_border_by_y = std::max({
            std::get<1>(input_data[0]) + std::get<2>(input_data[0]),  // y_1 + r_1
            std::get<1>(input_data[1]) + std::get<2>(input_data[1]),  // y_2 + r_2
            std::get<1>(input_data[2]) + std::get<2>(input_data[2])   // y_3 + r_3
        });

        L = left_border_by_x;
        R = right_border_by_x;
        T = top_border_by_y;
        B = bottom_border_by_y;
    }

    double square = (R - L) * (T - B);

    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> distX(L, R);
    std::uniform_real_distribution<double> distY(B, T);


    int64_t M = 0;
    for (int64_t i = 0; i < N; ++i) {
        double x = distX(rng);
        double y = distY(rng);

        if (
            (x - std::get<0>(input_data[0])) * (x - std::get<0>(input_data[0])) + ((y - std::get<1>(input_data[0])) * (y - std::get<1>(input_data[0]))) <= std::get<2>(input_data[0]) * std::get<2>(input_data[0]) &&
            (x - std::get<0>(input_data[1])) * (x - std::get<0>(input_data[1])) + ((y - std::get<1>(input_data[1])) * (y - std::get<1>(input_data[1]))) <= std::get<2>(input_data[1]) * std::get<2>(input_data[1]) &&
            (x - std::get<0>(input_data[2])) * (x - std::get<0>(input_data[2])) + ((y - std::get<1>(input_data[2])) * (y - std::get<1>(input_data[2]))) <= std::get<2>(input_data[2]) * std::get<2>(input_data[2])
        ) {
            ++M;
        }
    }

    double res = static_cast<double>(M) / N * square;

    std::cout << std::fixed << std::setprecision(10) << res << '\n';
    return 0;
}
