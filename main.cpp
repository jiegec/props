/*
 *  This file is part of props
 *  Copyright (c) 2017 props's authors.
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>
#include "prop.h"

int main() {
    int prop[26] = {0}, prop_num = 0;
    char prop_name[26] = {0};
    bool permu[27] = {false};

    while (true) {
        char buffer[1024];
        char temp;
        size_t len = 0;
        auto action = 0, count = 0;
        Expression *exp = nullptr;
        std::vector<int> v_or, v_and;

        printf("0: Quit program\n1: Show T/F Table\n2: Generate Formula from T/F Table\n3: Get Main Formulas\n");
        printf("Enter action(0-3):");
        while (true) {
            fgets(buffer, sizeof(buffer), stdin);
            if (strlen(buffer) && buffer[0] != '\n')
                break;
        }
        action = atoi(buffer);
        switch (action) {
            case 1:
                memset(prop, 0, sizeof(prop));
                memset(permu, 0, sizeof(permu));
                prop_num = 0;

                printf("Enter formula(~ for not, /\\ for and, \\/ for or, -> for implies, <-> for double implies):\n");
                while (true) {
                    fgets(buffer, sizeof(buffer), stdin);
                    if (strlen(buffer) && buffer[0] != '\n')
                        break;
                }

                parse_expression(&exp, buffer);
                // Collect props alphabetically
                mark_props(exp, prop, prop_num);
                count = 0;
                for (auto i = 0; i < 26; i++) {
                    if (prop[i]) {
                        prop[i] = ++count;
                        prop_name[count] = (char) (i + 'A');
                    }
                }

                for (auto i = 1; i <= prop_num; i++) {
                    printf(" %c ", prop_name[i]);
                }
                printf(" RESULT \n");

                do {
                    for (auto i = 1; i <= prop_num; i++) {
                        printf(" %c ", permu[i] ? 'T' : 'F');
                    }
                    printf(" %c \n", calc(exp, prop, permu) ? 'T' : 'F');
                } while (next_permutation(prop_num, permu));

                break;
            case 2:
                memset(prop, 0, sizeof(prop));
                memset(permu, 0, sizeof(permu));
                prop_num = 0;

                printf("Enter propositions(separated by one space):\n");
                fgets(buffer, sizeof(buffer), stdin);

                len = strlen(buffer);
                for (auto i = 0; i < len; i += 2) {
                    prop[prop_num++] = buffer[i];
                    prop_name[prop_num] = buffer[i];
                }

                for (auto i = 1; i <= prop_num; i++) {
                    printf(" %c ", prop_name[i]);
                }
                printf(" RESULT \n");

                count = 0;
                do {
                    for (auto i = 1; i <= prop_num; i++) {
                        printf(" %c ", permu[i] ? 'T' : 'F');
                    }
                    while (true) {
                        scanf("%c", &temp);
                        if (temp == 'T') {
                            v_or.push_back(count);
                            break;
                        } else if (temp == 'F')
                            break;
                    }
                    count++;
                } while (next_permutation(prop_num, permu));

                printf("\\/_{");
                printf("%s", std::accumulate(v_or.begin(), v_or.end(), std::string(),
                                             [](const std::string &a, int b) -> std::string {
                                                 return a + (a.empty() ? "" : ", ") + std::to_string(b);
                                             }).c_str());
                printf("}\n");

                printf("%s", std::accumulate(v_or.begin(), v_or.end(), std::string(),
                                             [=](const std::string &a, int b) -> std::string {
                                                 std::stringstream ss;
                                                 ss << "(";
                                                 for (auto i = 1; i <= prop_num; i++) {
                                                     if (!(b & (1 << (prop_num - i)))) {
                                                         ss << "~";
                                                     }
                                                     ss << prop_name[i];
                                                     if (i != prop_num)
                                                         ss << " /\\ ";
                                                 }
                                                 ss << ")";
                                                 return a + (a.empty() ? "" : " \\/ ") + ss.str();
                                             }).c_str());
                printf("\n");
                break;
            case 3:
                memset(prop, 0, sizeof(prop));
                memset(permu, 0, sizeof(permu));
                prop_num = 0;

                printf("Enter formula(~ for not, /\\ for and, \\/ for or, -> for implies, <-> for double implies):\n");
                while (true) {
                    fgets(buffer, sizeof(buffer), stdin);
                    if (strlen(buffer) && buffer[0] != '\n')
                        break;
                }

                parse_expression(&exp, buffer);
                // Collect props alphabetically
                mark_props(exp, prop, prop_num);
                count = 0;
                for (auto i = 0; i < 26; i++) {
                    if (prop[i]) {
                        prop[i] = ++count;
                        prop_name[count] = (char) (i + 'A');
                    }
                }
                count = 0;
                do {
                    if (calc(exp, prop, permu)) {
                        v_or.push_back(count);
                    } else {
                        v_and.push_back((1 << prop_num) - 1 - count);
                    }
                    count++;
                } while (next_permutation(prop_num, permu));

                printf("\\/_{");
                printf("%s", std::accumulate(v_or.begin(), v_or.end(), std::string(),
                                             [](const std::string &a, int b) -> std::string {
                                                 return a + (a.empty() ? "" : ", ") + std::to_string(b);
                                             }).c_str());
                printf("}\n");

                printf("/\\_{");
                printf("%s", std::accumulate(v_and.rbegin(), v_and.rend(), std::string(),
                                             [](const std::string &a, int b) -> std::string {
                                                 return a + (a.empty() ? "" : ", ") + std::to_string(b);
                                             }).c_str());
                printf("}\n");
                break;
            case 0:
            default:
                printf("Goodbye!\n");
                return 0;
        }
        free_expression(&exp);
    }
}
