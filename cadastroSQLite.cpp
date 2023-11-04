#include <iostream>
#include <iomanip>
#include <string>
#include <sqlite3.h>
#include "myLibc++.cpp"
using namespace std;

/*
bool validEmail(string text)
{
    std::string charArrayString(text);

    size_t foundAt =  charArrayString.find("@");
    size_t foundCom =  charArrayString.find(".com");

    if (foundAt != std::string::npos && foundCom != std::string::npos){
            return true;
    }

    return false;
}
*/

void inserir(sqlite3 *db) {
    char *erro;
    string nome, rua, bairro, estado, email, cep, celular;
    string cpf, rg;
    clearscr();
    
    cout << endl
         << endl
         <<"Cadastro de contatos " << endl;
    
    cout << "Nome: ";
    nome = leStr();
    cout << "Rua: ";
    rua = leStr();
    cout << "Bairro: ";
    bairro = leStr();
    cout << "Estado: ";
    estado = leStr();
    
    do{
        cout << "E-mail: ";
        email = leStr();
    }while(!validEmail(email));

    cout << "Cep: ";
    cep = leStr();
    cout << "Celular: ";
    celular = leStr();

    do{
        cout << "Cpf: ";
        cpf = leStr();
    }while(!cpfTest(cpf));

    do{
        cout << "Rg: ";
        rg = leStr();
    }while(!rgTest(rg));


    char sql_c[200];
    
    sprintf(sql_c, "INSERT INTO contatos (nome,rua,bairro,estado,email,cep,celular,cpf,rg) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s');",
            nome.c_str(), rua.c_str(), bairro.c_str(), estado.c_str(), email.c_str(), cep.c_str(), celular.c_str(), cpf.c_str(), rg.c_str());
    
    int rc = sqlite3_exec(db, sql_c,NULL, NULL, &erro);
    if (rc != SQLITE_OK){
        cerr << "Erro " << erro << endl;
        return;
    }
}

void matar (sqlite3 *db){
    char *erro;
    
    string sql = "DROP TABLE contatos;";
    
    int rc = sqlite3_exec(db, sql.c_str(),NULL, NULL, &erro);
    if (rc != SQLITE_OK){
        cerr << "Erro " << erro << endl;
        return ;
    }
    exit(-1);
}

void listar(sqlite3 *db){
    sqlite3_stmt *stmt;
    char *erro;
    const unsigned char *nome;
    const unsigned char *rua;
    const unsigned char *bairro;
    const unsigned char *estado;
    const unsigned char *email;
    const unsigned char *cep;
    const unsigned char *celular;
    const unsigned char *cpf;
    const unsigned char *rg;
    int id;
   

    int rs = sqlite3_prepare_v2(db, "SELECT * FROM contatos;", -1, &stmt, 0);
    clearscr();
    cout << endl
         << endl
         << "Agenda" << endl;

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        id = sqlite3_column_int(stmt, 0);
        nome = sqlite3_column_text(stmt, 1);
        rua = sqlite3_column_text(stmt,2);
        bairro = sqlite3_column_text(stmt,3);
        estado = sqlite3_column_text(stmt,4);
        email = sqlite3_column_text(stmt,5);
        cep = sqlite3_column_text(stmt,6);
        celular = sqlite3_column_text(stmt,7);
        cpf = sqlite3_column_text(stmt,8);
        rg = sqlite3_column_text(stmt,9);          

        cout << "\n---------------------------------------------------------";
        cout << '\n' << setw(30) << left << "ID: " << id << '\n'
             << setw(30) << left <<"Nome: " <<  nome << '\n'
             << setw(30) << left << "Rua: " << rua << '\n'
             << setw(30) << left << "Bairro: " << bairro << '\n'
             << setw(30) << left << "Estado: " << estado << '\n'
             << setw(30) << left << "E-mail: " << email << '\n'
             << setw(30) << left << "Cep: " << cep << '\n'
             << setw(30) << left << "Celular: " << celular << '\n'
             << setw(30) << left << "Cpf: " << cpf << '\n'
             << setw(30) << left << "Rg: " << rg << '\n';
        cout << "---------------------------------------------------------\n";
    }
}

int consulta(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
    char *erro;
    const unsigned char *nome;
    const unsigned char *rua;
    const unsigned char *bairro;
    const unsigned char *estado;
    const unsigned char *email;
    const unsigned char *cep;
    const unsigned char *celular;
    const unsigned char *cpf;
    const unsigned char *rg;

    char sql[200];
    sprintf(sql, "SELECT * FROM contatos WHERE ID = %d;",id);
    int rs = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    rs = sqlite3_step(stmt);
    if (rs == 100){
    id = sqlite3_column_int(stmt, 0);
        nome = sqlite3_column_text(stmt, 1);
        rua = sqlite3_column_text(stmt,2);
        bairro = sqlite3_column_text(stmt,3);
        estado = sqlite3_column_text(stmt,4);
        email = sqlite3_column_text(stmt,5);
        cep = sqlite3_column_text(stmt,6);
        celular = sqlite3_column_text(stmt,7);
        cpf = sqlite3_column_text(stmt,8);
        rg = sqlite3_column_text(stmt,9);   
        
        cout << "\n---------------------------------------------------------";
        cout << '\n' << setw(30) << left << "ID: " << id << '\n'
             << setw(30) << left <<"Nome: " <<  nome << '\n'
             << setw(30) << left << "Rua: " << rua << '\n'
             << setw(30) << left << "Bairro: " << bairro << '\n'
             << setw(30) << left << "Estado: " << estado << '\n'
             << setw(30) << left << "E-mail: " << email << '\n'
             << setw(30) << left << "Cep: " << cep << '\n'
             << setw(30) << left << "Celular: " << celular << '\n'
             << setw(30) << left << "Cpf: " << cpf << '\n'
             << setw(30) << left << "Rg: " << rg << '\n';
        cout << "---------------------------------------------------------\n";
    } else {
        cout << "ID nao encontrado!" << endl;
        return 0;
    }
    return 1;
}

void alterar (sqlite3 *db){
    char *erro;
    string nome, rua, bairro, estado, email, cep, celular;
    string cpf, rg;
    int id;
    char sql_c[200];
    cout << "Qual o codigo do registro a ser alterado: ";
    cin >> id;
    int ok = consulta(db, id);
    if (! ok) return;
    int op;

    cout << "1) Nome:     " << endl;
    cout << "2) Rua:      " << endl;
    cout << "3) Bairro:   " << endl;
    cout << "4) Estado:   " << endl;
    cout << "5) Email:    " << endl;
    cout << "6) CEP:      " << endl;
    cout << "7) Celular:  " << endl;
    cout << "8) CPF:      "<< endl;
    cout << "9) RG:       "<< endl;
    
    cout << "Qual campo sera alterado: ";
    cin >> op;
    switch (op)
    {
    case 1:
        cout << "Nome: ";
        nome = leStr();
        sprintf(sql_c, "UPDATE contatos SET NOME = '%s' WHERE ID = %d;",nome.c_str(),id);
        break;
    case 2:
        cout << "Rua: " ;
        celular = leStr();
        sprintf(sql_c, "UPDATE contatos SET CELULAR = '%s' WHERE ID = %d;",celular.c_str(),id);
        break;
    case 3:
        cout << "Bairro: " ;
        bairro = leStr();
        sprintf(sql_c, "UPDATE contatos SET BAIRRO = '%s' WHERE ID = %d;",bairro.c_str(),id);
        break;
    case 4:
        cout << "Estado: " ;
        estado = leStr();
        sprintf(sql_c, "UPDATE contatos SET ESTADO = '%s' WHERE ID = %d;",estado.c_str(),id);
        break;
    case 5:
        cout << "Email: " ;
        email = leStr();
        sprintf(sql_c, "UPDATE contatos SET EMAIL = '%s' WHERE ID = %d;",email.c_str(),id);
        break;
    case 6:
        cout << "CEP: " ;
        cep = leStr();
        sprintf(sql_c, "UPDATE contatos SET CEP = '%s' WHERE ID = %d;",cep.c_str(),id);
        break;
     case 7:
        cout << "Celular: " ;
        celular = leStr();
        sprintf(sql_c, "UPDATE contatos SET CELULAR = '%s' WHERE ID = %d;",celular.c_str(),id);
        break;
     case 8:
        cout << "CPF: " ;
        cpf = leStr();
        sprintf(sql_c, "UPDATE contatos SET CPF = '%s' WHERE ID = %d;",cpf.c_str(),id);
        break;
    case 9:
        cout << "RG: " ;
        rg = leStr();
        sprintf(sql_c, "UPDATE contatos SET RG = '%s' WHERE ID = %d;",rg.c_str(),id);
        break;
    default:
        cout << "Alteracao cancelada" << endl;
        return;
    }
    int rc = sqlite3_exec(db, sql_c,NULL, NULL, &erro);
    if (rc != SQLITE_OK){
        cerr << "Erro " << erro << endl;
        return ;
    }
    cout << "Dados alterados com sucesso (enter) para continuar ";
}

void excluir (sqlite3 *db){
    char *erro;
    int id;
    cout << "Codigo da exclusao: ";
    cin >> id;
	char sql_c[200];
    
    //Deleta um contato
    sprintf(sql_c, "DELETE FROM contatos WHERE ID = %d;",id);
    int rc = sqlite3_exec(db, sql_c,NULL, NULL, &erro);
    if (rc != SQLITE_OK){
        cerr << "Erro " << erro << endl;
        return ;
    }
}



int main(int argc, char const *argv[])
{
    char *erro;
    sqlite3 *db;
    sqlite3_open("agenda.db", &db); //armazena o endereço no ponteiro

    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS contatos (id integer primary key autoincrement, nome varchar(30), rua varchar(100), bairro varchar(30), estado varchar(30), email varchar(100), cep varchar(10), celular varchar(20), cpf varchar(15), rg varchar(15))", NULL, NULL, &erro);
    if (rc != SQLITE_OK){
        cerr << "Erro " << erro << endl;
        return -1;
    }

    int op = 1;
    while (op){
        clearscr();
        cout << endl;
        cout << " 1 - Cadastrar" << endl;
        cout << " 2 - Listar" << endl;
        cout << " 3 - Consultar" << endl;
        cout << " 4 - Alterar" << endl;
        cout << " 5 - Excluir" << endl;
        cout << " 0 - Fim" << endl;
        cout << "Opcao: ";
        cin >> op;
        char cont = 's';
               
        switch (op){
            case 1 :
                while (cont == 's'){ 
                  inserir(db); 
                  cout << "Novo cadastro [s/n]: ";
                  cin >> cont;
                }
                break;
            case 2 :
                listar(db);
                pausa();
				break;
            case 3 :
                int id;
                clearscr();
                cout << "Qual o codigo: ";
                cin >> id;
                consulta(db, id);
                pausa();
				break;
            case 4:
                alterar(db);
            	pausa();
                break;
            case 5 :
                excluir(db);
                pausa();
                break;
            case -1:
                matar(db);
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida" << endl;
                pausa();
        }
    }
    
    sqlite3_close(db);
    return 0;
}
    