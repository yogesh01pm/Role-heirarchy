#include<bits/stdc++.h>
using namespace std;

class role 
{
    public:
        string rolename;
        string headrole;
        static int count;
        int roleno;
        list<string> userlist;
        list<string> employee; 
        void setid()
        {
            count++;
            
        }
        role()
        {
            roleno=-1;
        }
        role(string newrole) 
        {
            setid();
            rolename=newrole;
            this->headrole="\0";
        }
        role(string newrole,string headrole)
        {
            setid();
            rolename=newrole;
            this->headrole=headrole;
        }
        
};
class ZOHO
{
    public:
        role rootrole; 
        list<role> hierarchy; 
        list<pair<string,string>> allUser; 
        int sizeOfHierarchy=0;
        void display()/*bfs search*/
        {
            queue<string> que;
            que.push(rootrole.rolename);
            while(!que.empty())
            {
                string currentrolename=que.front();
                role *currentrole=findrolebyname(currentrolename);
                for(string employeeroles : currentrole->employee)
                {
                    que.push(employeeroles);
                }
                if(rootrole.rolename!=currentrolename)
                cout<<",";
                cout<<currentrolename;
                que.pop();
            }
            cout<<endl;
        }
        void setroot(role r)
        {
            rootrole=r;
            hierarchy.push_back(r);
        }
        role *findrolebyname(string name)
        {
            for(role &head : hierarchy)
            {
                if(head.rolename==name)
                return &head;
            }
            cout<<"role is not available\n";
            role norole;
            return NULL;
        }
        void addrole(role r) 
        {
            sizeOfHierarchy++;
            hierarchy.push_back(r);
            role *head=findrolebyname(r.headrole);
            if(head!=NULL)
            head->employee.push_back(r.rolename);    
        }
        void deleterole(string removerole,string headrole) 
        {
            sizeOfHierarchy--;
            role *todelete=findrolebyname(removerole);
            role *headOfdelete=findrolebyname(todelete->headrole);
            role *newhead=findrolebyname(headrole);
            headOfdelete->employee.remove(removerole);
            newhead->employee.merge(todelete->employee);
            newhead->userlist.merge(todelete->userlist);
                        list<role> temp;
            for(role &r : hierarchy)
            {
                if(r.rolename!=removerole)
                {
                    temp.push_back(r);
                }
            }
            hierarchy=temp;
            for(auto &userpair : allUser)
            {
                if(userpair.second==removerole)
                    userpair.second=headrole;
            }
        }
        list<string> mergeuser(role *currentrole)
        {
            list<string> subs,currentroleuser;
            currentroleuser=currentrole->userlist;
            for(auto subrole : currentrole->employee)
            {
                subs.merge(mergeuser(findrolebyname(subrole)));
            }
            subs.merge(currentroleuser);
            return subs;
        }
        list<string> dfsonuser(string name)
        {
            list<string> subs,currentRoleUser;
            role *currentrole=findrolebyname(name);
            currentRoleUser=currentrole->userlist;
            for(auto subrole : currentrole->employee)
            {
                subs.merge(dfsonuser(subrole));
            }
            for(auto &currentuser : currentRoleUser)
            {
                cout<<currentuser<<"->";
                for(auto strit=subs.begin();strit!=subs.end();strit++)
                {
                    if(strit!=subs.begin())
                    cout<<",";
                    cout<<(*strit);
                }
                cout<<endl;
            }
            subs.merge(currentRoleUser);
            return subs;
        }

        
        int maxheight(string name)/*dfs search*/
        {
            role *currentrole=findrolebyname(name);
            int maxofemployee=0;
            if(currentrole->employee.empty())
            return 0;
            else
            {   
                for(string &employeerole : currentrole->employee)
                    maxofemployee=max(maxofemployee,maxheight(employeerole));
                return 1+maxofemployee;
            }
        }
        void lcaofusers(role *currentrole,string user1,string user2)
        {
           list<string> subs;
           bool found1=false,found2=false;
           if(currentrole->userlist.empty())
           {
               for(auto &employee : currentrole->employee)
               {
                    lcaofusers(findrolebyname(employee),user1,user2);
               }
           }
           else
           {
               subs=mergeuser(currentrole);
               for(auto &str : subs)
                {
                if(str==user1)
                found1=true; 
                if(str==user2)
                found2=true;
                }
                if(found1 && found2)
                {
                    cout<<"Top most common bosses:"<<endl;
                    for(auto str=currentrole->userlist.begin();str!=currentrole->userlist.end();str++)
                    {
                        if(str!=currentrole->userlist.begin())
                        cout<<",";
                        cout<<(*str);
                    }
                    cout<<endl;
                }
           }
        }
};
int role::count=0;
int main()
{
    int option,countuser;
    ZOHO z;
    role r;
    role *roleofuser;
    string newrole,headrole,removerole,name,user1,user2;
    cout<<"Enter root role name:";
    getline(cin,newrole);
    r=role(newrole);
    z.setroot(r);
    cout<<"The Company Owner is:"<<newrole<<endl;
    do
    {
        cout<<"-----------------------------------------------------------------------------"<<endl;
        cout<<"OPERATIONS:"<<endl;
        cout<<"\t1.Add sub role\n";
        cout<<"\t2.Display roles\n";
        cout<<"\t3.Delete role\n";
        cout<<"\t4.Add user\n";
        cout<<"\t5.Display users\n";
        cout<<"\t6.Display users and Sub users\n";
        cout<<"\t7.Delete user\n";
        cout<<"\t8.Number of users from top\n";
        cout<<"\t9.Height of role hierarchy\n";
        cout<<"\t10.Common boss of users\n";
        cout<<"\t0.Exit\n";
         cout<<"-----------------------------------------------------------------------------"<<endl;
        cin>>option;
        countuser=0;
        if(option>0 && option<=10)
        cout<<"-----------------------------------------------------------------------------"<<endl;
        cout<<"Operation to be performed : "<<option<<endl;
        cout<<"-----------------------------------------------------------------------------"<<endl;
        switch(option)
        {
            case 0 :break;
            case 1 :cout<<"Enter sub role name:";
                    cin.ignore();
                    getline(cin,newrole);
                    cout<<"Enter reporting to role name:";
                    getline(cin,headrole);
                    r=role(newrole,headrole);
                    z.addrole(r);
                    break;
            case 2 :z.display();
                    break;
            case 3 :cin.ignore();
                    cout<<"Enter the role to be deleted:";
                    getline(cin,removerole);
                    cout<<"Enter the role to be transferred:";
                    getline(cin,headrole);
                    z.deleterole(removerole,headrole);
                    break;
            case 4 :cin.ignore();
                    cout<<"Enter user name:";
                    getline(cin,name);
                    cout<<"Enter role:";
                    getline(cin,newrole);
                    roleofuser=z.findrolebyname(newrole);
                    if(roleofuser!=NULL)
                    {
                        roleofuser->userlist.push_back(name);
                    z.allUser.push_back(make_pair(name,newrole)); 
                    }
                    break;
            case 5 :for(auto &userpair : z.allUser)
                    {
                        cout<<userpair.first<<"->"<<userpair.second<<endl;
                    }
                    break;
            case 6 :z.dfsonuser(z.rootrole.rolename);
                    break;
            case 7 :cin.ignore();
                    cout<<"Enter user name to be deleted! :";
                    getline(cin,name);
                    newrole="\0";
                    for(auto userpair=z.allUser.begin();userpair!=z.allUser.end();userpair++)
                    {
                        if(userpair->first==name)
                        {
                            newrole=userpair->second;
                            z.allUser.erase(userpair);
                            break;
                        }
                    }
                    if(newrole!="\0")
                    {
                        roleofuser=z.findrolebyname(newrole);
                    if(roleofuser!=NULL)
                        roleofuser->userlist.remove(name);
                    }
                    else
                    cout<<"Not found!!!! \n";
                    break;
            case 8 :cin.ignore();
                    cout<<"Enter user name:";
                    getline(cin,name);
                    newrole="\0";
                    for(auto userpair=z.allUser.begin();userpair!=z.allUser.end();userpair++)
                    {
                        if(userpair->first==name)
                        {
                            newrole=userpair->second;
                            break;
                        }
                    }
                    if(newrole!="\0")
                    {
                        roleofuser=z.findrolebyname(newrole);
                    }
                    else
                    {
                        cout<<"user not found!!!!"<<endl;
                        break;
                    }
                    while(roleofuser->headrole!="\0")
                    {
                        roleofuser=z.findrolebyname(roleofuser->headrole);
                        if(roleofuser==NULL)
                        break;
                        countuser+=roleofuser->userlist.size();
                    }
                    cout<<"Number of users from top:"<<countuser<<endl;
                    break;
            case 9 :cout<<"Height of hierarchy:"<<z.maxheight(z.rootrole.rolename)+1<<endl;
                    break;
            case 10 :cin.ignore();
                    cout<<"Enter first user:";
                    getline(cin,user1);
                    cout<<"Enter second user:";
                    getline(cin,user2);
                    z.lcaofusers(z.findrolebyname(z.rootrole.rolename),user1,user2);
                    break;
            default :cout<<"Invalid operation!!!!\n";
        }
    } while (option!=0);

    return 0;
}

