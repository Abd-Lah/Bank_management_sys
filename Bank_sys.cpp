#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;
struct Client {
    int Id_client;
    char Nom[20];
    char Prenom[20];
    char Profession[30];
    char Num_tel[14];
};
struct Compte{
    int Id_compte;
    int Id_clt;
    float Solde;
    char D_ouver [12];
};
void Creation_client(Client*,const int&);
void Ecrire(Client*,int&);
void Lecture_Client(Client*,int&);
void Affiche_client(Client*,const int&);
int size_file();
void Lecture_Compte(Compte*,int&);
void Affiche_compte(Compte*,const int&);
void Ajouter (Client*,int&);
void Modifier (Client*,int&,int&);
void Supprimer (Client*,Compte*,int&,int&);
void Chercher (Client*,int&,int&);
void ajoute(Client*,int&,Compte*,const int&);
void Creation_compte(Compte*);
void consulter_solde(Compte*,int&,int&);
void Fermer_compte(Compte*,int&,int&);
void Retirer_montant(Compte*,int&,int&,float&);
void Verser_montant(Compte*,int&,int&,float&);
int main (){
    int id,N,rep;
    float montant;
    char retour;
    id = -1;
    N = 0;
    Client* clt ;
    clt = new Client ;
    Compte* cmpt;
    cmpt = new Compte ;
    cout <<"\t\t================= MENU GENERAL ================="<<endl;
    cout <<"\n\t1. Gestion des clients\t\t\t\t2. Gestion des comptes\n\t3. Gestion des operations"
         <<"\t\t\t4. QUITTER"<<endl;
    cout <<"___________________________________________________________________"<<endl;
    cout <<"\n\t5. Table clients\t\t\t\t6. Table comptes"<<endl;

    do{
        cout <<"\t\t---->Entrer votre choi : ";cin >> rep;
    }while(rep>6 || rep < 1);
    switch(rep){
        case 1:
                cout <<"\t\t\t______ Gestion des clients ______"<<endl;
                cout <<"\t1) Ajouter\t\t\t2) Modifier\n\t3) Supprimer\t\t\t4) chercher"
                     <<"(par son Identificateur.)"<<endl;
                do{
                    cout <<"\t\t-->Entrer votre choix : ";cin >> rep;
                }while(rep>4 || rep < 1);
                switch(rep){
                    case 1:cout<<"\t\t---->Nombre des client : ";cin>>N;
                        clt = new Client[N];
                        Ecrire(clt,N);break;
                    case 2:Modifier(clt,N,id);break;
                    case 3:Supprimer(clt,cmpt,N,id);break;
                    case 4:Chercher(clt,N,id);break;
                    default:break;
                }break;
        case 2:
                cout <<"\t\t\t______ Gestion des Compte ______"<<endl;
                cout <<"\t1) Crier un compte(par son Identificateur.)\t\t\t2) Consulter le solde\n\t3) Fermer un compte"<<endl;
                do{
                    cout <<"\t\t---->Entrer votre choi : ";cin >> rep;
                }while(rep>3 || rep < 1);
                switch(rep){
                    case 1: cout<<"\t\t---->Id de client : ";cin>>id;
                        ajoute(clt,N,cmpt,id);break;
                    case 2: consulter_solde(cmpt,N,id);break;
                    case 3: Fermer_compte(cmpt,N,id);break;
                    default:break;
                }break;
        case 3:
                cout <<"\t\t\t______ Gestion des operation ______"<<endl;
                cout <<"\t1) Retirer montant \t\t\t\t2)Verser montant"<<endl;
                do{
                    cout <<"\t\t---->Votre Choix : ";cin >>rep;
                }while(rep>3 || rep<1);
                switch(rep){
                    case 1: Retirer_montant(cmpt,N,id,montant);break;
                    case 2: Verser_montant(cmpt,N,id,montant);break;
                    default: break;
                }break;
        case 5: Lecture_Client(clt,N);Affiche_client(clt,N);break;
        case 6: Lecture_Compte(cmpt,N);Affiche_compte(cmpt,N);break;
        default: break;
    }
    delete [] clt;
    delete [] cmpt;
    cout <<"Retour au menu principale [y/n] ";cin >> retour;
    if(retour == 'y' || retour == 'Y'){
        main();
    }
    else{
        system("pause");
        return 0;
    }
}
void Affiche_client(Client* Tab,const int& N){
    cout <<"\t\t\t ________ Table des clients ________"<<endl;
    cout <<"\t+-------+--------------------+--------------------+--------------------+--------------+"<<endl;
    cout <<"\t|Id_clt |Nom                 |Prenom              |Profession          |Phone number  |"<<endl;
    cout <<"\t+-------+--------------------+--------------------+--------------------+--------------+"<<endl;
    for(int i = 0;i<N;i++){
        printf("\t|%7d|%20s|%20s|%20s|%14s|\n",Tab[i].Id_client,Tab[i].Nom,Tab[i].Prenom,Tab[i].Profession,Tab[i].Num_tel);
        cout <<"\t+-------+--------------------+--------------------+--------------------+--------------+"<<endl;
    }
}
void Affiche_compte(Compte* Tab,const int& N){
        cout <<"\t ________ Table des Comptes ________"<<endl;
        cout <<"\t+-------+-------+------------+--------------+"<<endl;
        cout <<"\t|Id_cpt |Id_clt |Solde DH    |Date d ouvrir |"<<endl;
        cout <<"\t+-------+-------+------------+--------------+"<<endl;
        for(int i = 0;i<N;i++){
            printf("\t|%7d|%7d|%12.2f|%14s|\n",Tab[i].Id_compte,Tab[i].Id_clt,Tab[i].Solde,Tab[i].D_ouver);
            cout <<"\t+-------+-------+------------+--------------+"<<endl;
        }
}
void Creation_client(Client* clt,const int& N){
    ofstream data1("gestion.txt");
    if(data1){
        cout <<"Le fichier ouvert avec succes (:"<<endl;
        for(int i = 0;i<N;i++){
            if(i == N-1){
                data1 <<clt[i].Id_client<<" "<<clt[i].Nom<<" "<<clt[i].Prenom<<" "<<clt[i].Profession
                      <<" "<<clt[i].Num_tel;
            }else {
                data1 <<clt[i].Id_client<<" "<<clt[i].Nom<<" "<<clt[i].Prenom<<" "<<clt[i].Profession
                      <<" "<<clt[i].Num_tel<<endl;
            }
        }
        data1.close();
    }else cerr <<"echec d ouverture de fichier !"<<endl;
}
void Ecrire(Client* clt,int& N){
    for(int i = 0;i<N;i++){
        cout <<"Entrer les informations de client "<<i+1<<" : "<<endl;
        cout <<"ID de client         : ";cin >>clt[i].Id_client;
        cout <<"Nom de client        : ";cin >>clt[i].Nom;
        cout <<"Prenom de client     : ";cin >>clt[i].Prenom;
        cout <<"Profession de client : ";cin >>clt[i].Profession;
        cout <<"Numero de telephone  : ";cin >>clt[i].Num_tel;
    }
    Ajouter(clt,N);
}
void Ajouter (Client* clt,int& N){
    ofstream data("gestion.txt",ios :: out | ios :: app);
    if(data.is_open()){
        cout <<"Le fichier ouvert avec succes (:"<<endl;
        data.seekp(0,ios :: end);
        for(int i = 0;i<N;i++){
            if(data.tellp() == 0){
                data <<clt[i].Id_client<<" "<<clt[i].Nom<<" "<<clt[i].Prenom<<" "<<clt[i].Profession
                     <<" "<<clt[i].Num_tel;
            }else data<<endl<<clt[i].Id_client<<" "<<clt[i].Nom<<" "<<clt[i].Prenom<<" "<<clt[i].Profession
                      <<" "<<clt[i].Num_tel;

        }
        data.close();
    }else cerr <<"echec d ouverture de fichier ):"<<endl;
}
void Lecture_Client(Client* Tab,int& N){
    ifstream data2("gestion.txt",ios :: in);
    if(data2){
        while(data2.eof() == 0){
            data2 >>Tab[N].Id_client>>Tab[N].Nom>>Tab[N].Prenom>>Tab[N].Profession>>Tab[N].Num_tel;
            N++;
        }
        data2.close();
    }else cerr <<"Aucune client !"<<endl;
}
int size_file(){
    int s;
    ifstream file( "gestion.txt", ios::in | ios::ate);
    if(file){
        s = (int)file.tellg();
        file.close();
        return s;
    }else return 0;
}
void Modifier(Client* Tab,int& N,int& id){
    if(size_file() != 0){
        Lecture_Client(Tab,N);
        int choix;
        char op;
        do{
            cout <<"Entrer l indice de client pour modifier ces information : ";cin>>id;
            int i = 0;
            while(Tab[i].Id_client != id && i<N){
                i++;
            }
            if(i != N){
                cout<<"1) Id\n2) Nom\n3) Prenom\n4) Profession\n5) Num_tel\n6) Exit)"<<endl;
                do{
                    cout<<"Entrer votre choi : ";cin>>choix;
                }while(choix>6 || choix<1);
                switch(choix){
                    case 1: cout <<"Old ID de client         : "<<Tab[i].Id_client<<endl;
                        cout <<"New ID de client         : ";
                        cin >>Tab[i].Id_client;
                        break;
                    case 2: cout <<"Old Nom de client        : "<<Tab[i].Nom<<endl;
                        cout <<"New Nom de client        : ";
                        cin >>Tab[i].Nom;
                        break;
                    case 3: cout <<"Old Prenom de client     : "<<Tab[i].Prenom<<endl;
                        cout <<"New Prenom de client     : ";
                        cin >>Tab[i].Prenom;
                        break;
                    case 4: cout <<"Old Profession de client : "<<Tab[i].Profession<<endl;
                        cout <<"New Profession de client : ";
                        cin >>Tab[i].Profession;
                        break;
                    case 5: cout <<"Old Numero de telephone   : "<<Tab[i].Num_tel<<endl;
                        cout <<"New Numero de telephone   : ";
                        cin >>Tab[i].Num_tel;
                        break;
                    default:break;
                }
            }else cout <<"Id n existe pas !"<<endl;
            cout <<"Autre modification[Y/N] ";cin>>op;
        }while(op == 'Y' || op == 'y');
        Creation_client(Tab,N);
    }else cout <<"echec d ouverture de fichier ):"<<endl;
}
void Supprimer (Client* Tab,Compte* cmpt,int& N,int& id){
    if(size_file() != 0){
        int M;
        Lecture_Client(Tab,N);
        Lecture_Compte(cmpt,M);
        cout <<"Entrer l id de client pour supprimer : ";cin>>id;
        int i = 0;
        while(i<N && Tab[i].Id_client != id){
            i++;
        }
        if(i != N){
            for(int j = i;j<N-1;j++){
                Tab[j] = Tab[j+1];
            }
            N--;
            Creation_client(Tab,N);
            i = 0;
            while(i<M && cmpt[i].Id_clt != id){
                i++;
            }
            if(i != M){
                id = cmpt[i].Id_compte;
                N = 0;
                Fermer_compte(cmpt,N,id);
            }
        }else cout <<"Id n existe pas !"<<endl;
    }else cout <<"echec d ouverture de fichier ):"<<endl;
}
void Chercher (Client* Tab,int& N,int& iD){
    if(size_file() != 0){
        int i;
        Lecture_Client(Tab,N);
        cout <<"Entrer l ID de client pour Chercher : ";cin>>iD;
        i = 0;
        while(Tab[i].Id_client != iD && i<N){
            i++;
        }
        if(i == N){
            cout<<"ID n existe pas !"<<endl;
        }else{
            cout <<"\t+-------+--------------------+--------------------+--------------------+--------------+"<<endl;
            cout <<"\t|Id_clt |Nom                 |Prenom              |Profession          |Phone number  |"<<endl;
            cout <<"\t+-------+--------------------+--------------------+--------------------+--------------+"<<endl;
            printf("\t|%7d|%15s|%15s|%15s|%14s|\n",Tab[i].Id_client,Tab[i].Nom,Tab[i].Prenom,Tab[i].Profession,Tab[i].Num_tel);
            cout <<"\t+-------+--------------------+--------------------+-------------------+--------------+"<<endl;
        }
    }else cout <<"echec d ouverture de fichier ):"<<endl;
}
void ajoute(Client* Tab,int& N,Compte* Crier_cpt,const int& id){
    if(size_file() != 0){
        Lecture_Client(Tab,N);
        int i = 0;
        while(i<N && Tab[i].Id_client != id){
            i++;
        }
        if(i!=N){
            cout <<"\tEntrer les informations de client  : "<<endl;
            cout <<"\tDate d ouverture     : ";cin >>Crier_cpt->D_ouver;
            cout <<"\tID de compte         : ";cin >>Crier_cpt->Id_compte;
            Crier_cpt->Id_clt = id;
            cout <<"\tSolde                : ";cin >>Crier_cpt->Solde;
            Creation_compte(Crier_cpt);
        }else cout <<"\t--->id n existe pas dans le fichier client "<<endl;
    }else cerr<<"\t--->aucune compte existe !"<<endl;
}
void Creation_compte(Compte* Crier_cpt){
    ofstream fich("gestionCompte.txt",ios :: out | ios :: app);
    if(fich.is_open()){
        cout <<"Le fichier ouvert avec succes (:"<<endl;
        fich<<Crier_cpt->Id_compte<<" "<<Crier_cpt->Id_clt<<" "<<Crier_cpt->Solde<<" "<<Crier_cpt->D_ouver<<endl;
        fich.close();
    }else cerr <<"\t-->echec d ouverture de fichier ):"<<endl;
}
void Lecture_Compte(Compte* Tab,int& N){
    ifstream fich("gestionCompte.txt");
    if(fich){
        cout <<"ouverture avec succes "<<endl;
        int pos;
        fich.seekg(-1,ios :: end);
        pos = (int)fich.tellg();
        fich.seekg(0,ios :: beg);
        while(fich.tellg() != pos){
            fich >>Tab[N].Id_compte>>Tab[N].Id_clt>>Tab[N].Solde>>Tab[N].D_ouver;
            N++;
        }
        fich.close();
    }else cerr <<"aucune compte existe !"<<endl;
}
void consulter_solde(Compte* Tab,int& N,int& id){
    Lecture_Compte(Tab,N);
    cout<<"Entrer l id de compte pour consulter son solde : ";cin >>id;
    int i;
    i = 0;
    while(i<N && Tab[i].Id_compte != id){
        i++;
    }
    if(i == N){
        cout <<"compte n existe pas !"<<endl;
    }else{
        cout<<"le solde de client est : "<<Tab[i].Solde<<" DH"<<endl;
    }

}
void Fermer_compte(Compte* Tab,int& N,int& id){
    Lecture_Compte(Tab,N);
    int i = 0;
    if(id == -1){
        cout<<"Entrer l id de compte pour Fermer : ";cin >>id;
    }
    while(i<N && Tab[i].Id_compte != id){
        i++;
    }
    if(i == N){
        cout <<"compte n existe pas !"<<endl;
    }else{
        remove("gestionCompte.txt");
        int j = N-1;
        while(j>i){
            Tab[i] = Tab[i+1];
            i++;
        }
        N--;
        for(int k = 0;k<N;k++){
            Creation_compte(&Tab[k]);
        }
    }
}
void Retirer_montant(Compte* Tab,int& N,int& id,float& montant){
    Lecture_Compte(Tab,N);
    cout <<"Id de compte : ";cin >>id;
    int i;
    i = 0;
    while(i<=N && Tab[i].Id_compte != id){
        i++;
    }
    if(i != N){
        Choisi_montant :{
        cout <<"Votre Solde : "<<Tab[i].Solde<<endl;
        int choix;
        cout <<"\t1) 100 dh\t\t\t\t2) 200 dh\n\t3) 300 dh\t\t\t\t4) 400 dh"
             <<"\n\t5) 500 dh\t\t\t\t6) 1000 dh\n\t7) autre montant"<<endl;
        do{
            cout <<"votre choix : ";
            cin >> choix;
        }while(choix<0 || choix>7);
        switch(choix){
            case 1: montant = 100;break;
            case 2: montant = 200;break;
            case 3: montant = 300;break;
            case 4: montant = 400;break;
            case 5: montant = 500;break;
            case 6: montant = 1000;break;
            case 7: cout <<"Entrer Montant : ";cin >>montant;break;
            default : break;
        }
        if(Tab[i].Solde<montant){
            cout <<"Votre solde insuffisant"<<endl;
            cout <<"Choisi un autre montant infirieure ou egal votre solde."<<endl;
            goto Choisi_montant;
        }else{
            Tab[i].Solde = Tab[i].Solde - montant;
            remove("gestionCompte.txt");
            for(int j = 0;j<N;j++){
                Creation_compte(&Tab[j]);
            }
        }
    }
    }else cout <<"compte n existe pas "<<endl;
}
void Verser_montant(Compte* Tab,int& N,int& id,float& montant){
    Lecture_Compte(Tab,N);
    cout <<"Id de compte : ";cin >>id;
    int i;
    i = 0;
    while(i<N && Tab[i].Id_compte != id){
        i++;
    }
    if(i != N){
        cout <<"Votre Solde : "<<Tab[i].Solde<<endl;
        int choix;
        cout <<"1) 100 dh\t\t\t\t2) 200 dh\n3) 300 dh\t\t\t\t4) 400 dh"
             <<"\n5) 500 dh\t\t\t\t6) 1000 dh\n7) autre montant"<<endl;
        do{
            cout <<"votre choix : ";
            cin >> choix;
        }while(choix<0 || choix>7);
        switch(choix){
            case 1: montant = 100;break;
            case 2: montant = 200;break;
            case 3: montant = 300;break;
            case 4: montant = 400;break;
            case 5: montant = 500;break;
            case 6: montant = 1000;break;
            case 7: cout <<"Entrer Montant : ";cin >>montant;break;
            default : break;
        }
        Tab[i].Solde = Tab[i].Solde + montant;
        remove("gestionCompte.txt");
        for(int j = 0;j<N;j++){
            Creation_compte(&Tab[j]);
        }
    }else cout <<"compte n existe pas "<<endl;
}
