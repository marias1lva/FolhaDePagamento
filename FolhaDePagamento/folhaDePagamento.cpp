#include <iomanip> // Proporciona controle de formatação de entrada e saída (ex: setw, setprecision)
#include <iostream> // Permite operações de entrada e saída (ex: cin, cout)
#include <locale> // Suporta a internacionalização e localização de programas (ex: setlocale)
#include <string> // Fornece a classe string para manipulação de cadeias de caracteres
#include <vector> // Define a classe vector para armazenar e gerenciar arrays dinâmicos
#include <chrono> // Para manipulação de tempo
#include <thread> // Para uso de funções de tempo
#include <sstream> // Para a função is_integer (verifica se uma string é um inteiro)
using namespace std;

// Função para verificar se uma string representa um número inteiro
bool is_integer(const string &s) {
    istringstream iss(s);
    int number;
    return (iss >> number) && (iss.eof());
}

int main() {
    // Permissão de caracteres especiais para suportar acentos e caracteres especiais
    setlocale(LC_ALL, "");

    // Variáveis
    int opcao_cadastro; // Variável para armazenar a opção do menu de cadastro
    string opcao_cadastro_str;
    int opcao_menu; // Variável para armazenar a opção do menu principal
    string opcao_menu_str;
    int opcao_relatorio; // Variável para armazenar a opção do menu de relatórios
    string opcao_relatorio_str;

    // Vetores para armazenar informações dos funcionários
    vector<string> funcionarios_nome;
    vector<string> funcionarios_cargo;
    vector<double> funcionarios_salario;
    vector<double> funcionarios_salario_hora;
    vector<double> funcionarios_horas_trabalhadas;

    string limpar_tela = "\x1B[2J\x1B[H";

    do {
        // Exibe o menu principal e solicita a opção do usuário
        cout << "\n*===============================================================*\n"
             << "Sistema de Folha de Pagamento\n"
             << "1. Página de Cadastros\n"
             << "2. Página de Relatórios\n"
             << "0. Sair\n"
             << "==================================================================\n"
             << "Digite um valor: ";
        cin >> opcao_menu_str;
        cout << endl;

        // Verifica se a entrada é um número inteiro válido
        while (!is_integer(opcao_menu_str) || (opcao_menu = stoi(opcao_menu_str)) < 0 || opcao_menu > 2) {
            cout << "Opção inválida, escolha uma das opções abaixo" << endl;
            cout << "\n*===============================================================*\n"
                 << "Sistema de Folha de Pagamento\n"
                 << "1. Página de Cadastros\n"
                 << "2. Página de Relatórios\n"
                 << "0. Sair\n"
                 << "==================================================================\n"
                 << "Digite um valor: ";
            cin >> opcao_menu_str;
            cout << endl;
        }

        cout << limpar_tela; // Limpa a tela após o valor inserido

        if (opcao_menu == 1) {
            do {
                // Exibe o menu de cadastros
                cout << "\n*===============================================================*\n"
                     << "Seção de Cadastros\n"
                     << "1. Cadastro de Funcionário\n"
                     << "2. Inserir Horas Trabalhadas e Salário por Hora\n"
                     << "0. Voltar\n"
                     << "==================================================================\n"
                     << "Digite um valor: ";
                cin >> opcao_cadastro_str; // Lê a opção escolhida pelo usuário no menu de cadastro
                cout << endl;

                // Verifica se a entrada é um número inteiro válido
                while (!is_integer(opcao_cadastro_str) || (opcao_cadastro = stoi(opcao_cadastro_str)) < 0 || opcao_cadastro > 2) {
                    cout << "Opção inválida, escolha uma das opções abaixo" << endl;
                    cout << "\n*===============================================================*\n"
                         << "Seção de Cadastros\n"
                         << "1. Cadastro de Funcionário\n"
                         << "2. Inserir Horas Trabalhadas e Salário por Hora\n"
                         << "0. Voltar\n"
                         << "==================================================================\n"
                         << "Digite um valor: ";
                    cin >> opcao_cadastro_str;
                    cout << endl;
                }

                cout << limpar_tela;

                // Se o usuário escolheu sair (opcao_cadastro == 0), sai do loop
                if (opcao_cadastro == 0) {
                    break;
                }

                if (opcao_cadastro == 1) {
                    string nome, cargo;

                    // Limpa o buffer de entrada após ler a opção de cadastro
                    cin.ignore(); // Ignora o caractere de nova linha deixado pelo cin >> anterior

                    // Lê o nome do funcionário
                    cout << "Digite o nome do funcionário: ";
                    getline(cin, nome);

                    // Lê o cargo do funcionário
                    cout << "Digite o cargo do funcionário: ";
                    getline(cin, cargo);

                    // Inicializa o salário e horas trabalhadas como zero
                    double salario_hora = 0.0;
                    double horas_trabalhadas = 0.0;
                    double salario = 0.0;

                    // Armazena as informações do funcionário nos vetores correspondentes
                    funcionarios_nome.push_back(nome);
                    funcionarios_cargo.push_back(cargo);
                    funcionarios_salario.push_back(salario);
                    funcionarios_salario_hora.push_back(salario_hora);
                    funcionarios_horas_trabalhadas.push_back(horas_trabalhadas);

                    cout << "Funcionário cadastrado com sucesso!\n\n";

                    this_thread::sleep_for(chrono::seconds(2));
                    cout << limpar_tela;

                } else if (opcao_cadastro == 2) {
                    // Verifica se há funcionários cadastrados
                    if (funcionarios_nome.empty()) {
                        cout << "Nenhum funcionário cadastrado ainda.\n";

                        this_thread::sleep_for(chrono::seconds(3));
                        cout << limpar_tela;

                    } else {
                        // Exibe a lista de funcionários cadastrados com seus índices
                        for (size_t i = 0; i < funcionarios_nome.size(); i++) {
                            cout << i + 1 << ". Nome: " << funcionarios_nome[i] << ", Cargo: " << funcionarios_cargo[i] << "\n";
                        }

                        int indice;
                        // Solicita ao usuário que escolha um número do funcionário para inserir as horas trabalhadas e o salário por hora
                        cout << "Escolha o número do funcionário para inserir horas trabalhadas e salário por hora: ";
                        cin >> indice;

                        // Verifica se o índice inserido é válido (dentro do intervalo de funcionários cadastrados)
                        if (indice > 0 && indice <= funcionarios_nome.size()) {
                            double salario_hora, horas_trabalhadas;

                            // Lê o salário por hora do funcionário
                            cout << "Digite o salário por hora do funcionário: R$";
                            cin >> salario_hora;

                            // Lê o número de horas trabalhadas pelo funcionário
                            cout << "Digite o número de horas trabalhadas pelo funcionário: ";
                            cin >> horas_trabalhadas;

                            // Calcula o salário do funcionário
                            double salario = salario_hora * horas_trabalhadas;

                            // Atualiza as informações do funcionário nos vetores correspondentes
                            funcionarios_salario_hora[indice - 1] = salario_hora;
                            funcionarios_horas_trabalhadas[indice - 1] = horas_trabalhadas;
                            funcionarios_salario[indice - 1] = salario;

                            cout << "Informações de salário e horas trabalhadas atualizadas com sucesso!\n";
                            this_thread::sleep_for(chrono::seconds(3));

                            cout << limpar_tela; // Limpa a tela após o valor inserido

                        } else {
                            cout << "Índice de funcionário inválido.\n";

                            this_thread::sleep_for(chrono::seconds(3));

                            cout << limpar_tela; // Limpa a tela após o valor inserido

                        }
                    }
                }

            } while (opcao_cadastro != 0); // Repete o menu de cadastro até o usuário optar por voltar

        } else if (opcao_menu == 2) {
            do {
                // Exibe o menu de relatórios
                cout << "\n*===============================================================*\n"
                     << "Seção de Relatórios\n"
                     << "1. Exibir a Folha de Pagamento\n"
                     << "2. Exibir a Quantidade de Funcionários\n"
                     << "3. Exibir a Média Salarial\n"
                     << "0. Voltar\n"
                     << "==================================================================\n"
                     << "Digite um valor: ";
                cin >> opcao_relatorio_str; // Lê a opção escolhida pelo usuário no menu de relatórios
                cout << endl;

                // Verifica se a entrada é um número inteiro válido
                while (!is_integer(opcao_relatorio_str) || (opcao_relatorio = stoi(opcao_relatorio_str)) < 0 || opcao_relatorio > 3) {
                    cout << "Opção inválida, escolha uma das opções abaixo" << endl;
                    cout << "\n*===============================================================*\n"
                         << "Seção de Relatórios\n"
                         << "1. Exibir a Folha de Pagamento\n"
                         << "2. Exibir a Quantidade de Funcionários\n"
                         << "3. Exibir a Média Salarial\n"
                         << "0. Voltar\n"
                         << "==================================================================\n"
                         << "Digite um valor: ";
                    cin >> opcao_relatorio_str;
                    cout << endl;
                }

                cout << limpar_tela;

                // Se o usuário escolheu sair (opcao_relatorio == 0), sai do loop
                if (opcao_relatorio == 0) {
                    break;
                }

                if (opcao_relatorio == 1) {
                    // Exibe a folha de pagamento
                    cout << "\nFolha de Pagamento:\n";
                    cout << left << setw(20) << "Nome"
                         << left << setw(20) << "Cargo"
                         << right << setw(20) << "Salário por Hora(R$)"
                         << right << setw(20) << "Horas Trabalhadas"
                         << right << setw(20) << "Salário(R$)" << "\n";
                    cout << string(100, '=') << "\n"; // Linha divisória

                    for (size_t i = 0; i < funcionarios_nome.size(); i++) {
                        cout << left << setw(20) << funcionarios_nome[i]
                             << left << setw(20) << funcionarios_cargo[i]
                             << right << setw(20) << fixed << setprecision(2) << funcionarios_salario_hora[i]
                             << right << setw(20) << fixed << setprecision(2) << funcionarios_horas_trabalhadas[i]
                             << right << setw(20) << fixed << setprecision(2) << funcionarios_salario[i] << "\n";
                    }

                    this_thread::sleep_for(chrono::seconds(3));

                    cout << limpar_tela;

                } else if (opcao_relatorio == 2) {
                    // Exibe a quantidade de funcionários cadastrados
                    cout << "Quantidade de Funcionários: " << funcionarios_nome.size() << "\n";

                    this_thread::sleep_for(chrono::seconds(3));

                    cout << limpar_tela;

                } else if (opcao_relatorio == 3) {
                    // Calcula e exibe a média salarial dos funcionários
                    double soma_salarios = 0;
                    for (double salario : funcionarios_salario) {
                        soma_salarios += salario;
                    }
                    double media_salarial;
                    if (funcionarios_salario.empty()) {
                        media_salarial = 0;
                    } else {
                        media_salarial = soma_salarios / funcionarios_salario.size();
                    }
                    cout << "Média Salarial: R$" << fixed << setprecision(2) << media_salarial << "\n";

                    this_thread::sleep_for(chrono::seconds(3));

                    cout << limpar_tela;

                }

            } while (opcao_relatorio != 0); // Repete o menu de relatórios até o usuário optar por voltar
        }
    } while (opcao_menu != 0); // Repete o menu principal até o usuário optar por sair

    // Mensagem de encerramento do programa
    cout << "Saindo do sistema...\n";
    cout << limpar_tela;

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}