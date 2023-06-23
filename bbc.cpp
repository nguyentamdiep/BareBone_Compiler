#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

class A{
    private:
        string getString(char x){
            string s(1, x);
            return s;  
        }
        string RemoveExtension(string str){
            string ans="";
            int i=str.size()-1;
            while (str[i] != '.'){
                i--;
            }
            i--;
            while (i>=0){
                ans = getString(str[i])+ans;
                i--;
            }
            return ans;

        }
        vector<string> split(string str){
          str += ' ';
          vector<string> ans;
          string temp = "";
        
          for(int i=0; i<(int)str.size(); i++){
            if(str[i] != ' '){
                temp += str[i];
            }
              else if (temp != "") {
                ans.push_back(temp);
                temp = "";
            }
          }
            
          return ans;
        }
        bool CheckComment(string s){
          
          vector<string> s1=split(s);
          if (s1[0]=="//"){
            return 1;
          }
          else if (s1[0][0]=='/' && s1[0][1]=='/'){
            return 1;
          }
          else{
            return 0;
          }
        }
    friend class BBtoCppCompiler;
    friend class CppCompiler;
    friend class CheckSyntaxError;

};

class CheckSyntaxError{
  private:
    bool CheckConvertToNumber(string s){
      for (int i=0;i<s.size();i++){
          if (s[i]<'0' || s[i] > '9'){
              return 0;
          }
      }
      return 1;
    }
    bool CheckVariable(string s){
      if (s[0]>='0' && s[0]<='9'){
        return 0;
      }
      int dem=0;
      for (int i=0;i<s.size();i++){
        if ((s[i]>='A' && s[i]<= 'Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9') || (s[i]=='_')){
          dem++;
        }
      }
      if (dem==s.size()){
        return 1;
      }
      else{
        return 0;
      }
    }
    string Convert1(string s){
        if (CheckConvertToNumber(s)){
            return "value";
        }
        else{
            string s1;
            if (s=="in")
                s1="inout";
            else if (s=="out")
                s1="inout";
            else if (s=="init")
                s1="initial";
            else if (s=="incr")
                s1="operator";
            else if (s=="decr")
                s1="operator";
            else if (s=="clear")
                s1="operator";
            else if (s=="while")
                s1="while";
            else if (s=="not")
                s1="not";
            else if (s=="do")
                s1="do";
            else if (s=="end")
                s1="end";
            else if (CheckVariable(s))
                s1="variable";
            return s1;
        }
    }
    vector<string> Convert2(vector<string> s){
        vector<string> s1;
        if (s.size()>= 1 && s[0] == "end"){
            s1.push_back("S");
            for (int i=1; i<s.size();i++){
                s1.push_back(s[i]);
            }
        }
        else if ((s.size()>= 2) && ((s[0]=="inout" && s[1]=="variable") || (s[0]=="operator" && s[1]=="variable"))){
            s1.push_back("S");
            for (int i=2; i<s.size();i++){
                s1.push_back(s[i]);
            }
        }
        else if ((s.size()>=3) && (s[0]=="initial" && s[1]=="variable" && s[2]=="value")){
            s1.push_back("S");
            for (int i=3;i<s.size();i++){
                s1.push_back(s[i]);
            }
        }
        else if ((s.size()>=5) && (s[0]=="while" && s[1]=="variable" && s[2]=="not" && s[3]=="value" && s[4]=="do")){
            s1.push_back("S");
            for (int i=5; i<s.size();i++){
                s1.push_back(s[i]);
            }
        }
        else
            s1=s;
        return s1;

    }
    bool CheckSyntax(vector<string> line){
        if (line.size()==0){
            return 1;
        }
        vector<string> st;
        for (int i=0;i<line.size();i++){
            st.push_back(Convert1(line[i]));
        }
        st=Convert2(st);
        if (st.size()==1 && st[0]=="S")
            return 1;
        else
            return 0;
        
    }
    
  public:
    bool CheckSyntaxAllLines(string filebb){
      ifstream file(filebb);
      if (!file){
            cout<<"Can not open file";
            return 0;
      }
      int nline=0;
      int n_errors=0;
      for (string str; getline(file, str);){
        nline++;
        A a;
        // if (str[0]=='/' && str[1]=='/'){
        //   continue;
        // }
        if (a.CheckComment(str)){
          continue;
        }
        string str1="";
        if (str[str.size()-1]==13){
          for (int i=0;i<str.size()-1;i++){
              str1+=str[i];
          }
        }
        else{
          for (int i=0;i<str.size();i++){
              str1+=str[i];
          }
        }
        
        vector<string> t;
        
        t=a.split(str1);
        
        if(!CheckSyntax(t)){
          n_errors++;
            cout<<"Syntax Error at line: "<<nline<<'\n';
        }
           
      }
      if (n_errors >0)
        return 0;
      else
        return 1;
    }

};

class BBtoCppCompiler{
  private:
  vector<string> STM;
  vector<string> variables;
    bool KiemTraNeuMotPhanTuThuocMotVector(string s, vector<string> a){
      for (int i=0;i<a.size();i++){
        if (a[i]==s)
          return 1;
      }
      return 0;
    }
    string convertBBtoCPP(string s){
      A a;
      vector<string> sv=a.split(s);
      string s1;
      if (sv.size()==0){
        s1='\n';
      }
      if ((sv.size()>=2) && sv[0]=="in"){
        s1 = "int "+sv[1]+";\n"+"cin>>"+sv[1]+";";
        this->variables.push_back(sv[1]);
      }
      else if ((sv.size()>=2) && sv[0]=="out"){
        s1 ="cout<<"+sv[1]+"<<\"\\n\""+";";
      }
      else if ((sv.size()>=3) && sv[0]=="init"){
        s1 ="int "+sv[1]+"="+sv[2]+";";
        this->variables.push_back(sv[1]);
      }
      else if ((sv.size()>=2) && sv[0]=="incr"){
        s1 =sv[1]+"++;";
      }
      else if ((sv.size()>=2) && sv[0]=="decr"){
        //s1 =sv[1]+"--;";
        s1=sv[1]+">0?"+sv[1]+"--:"+sv[1]+";";
      }
      else if ((sv.size()>=2) && sv[0]=="clear"){
        if (KiemTraNeuMotPhanTuThuocMotVector(sv[1], this->variables)){
          s1 =sv[1]+"=0;";
        }
        else{
          s1 ="int "+sv[1]+"=0;";
          this->variables.push_back(sv[1]);
        }
      }
      else if ((sv.size()>=5) && sv[0]=="while"){
        s1 ="while ("+sv[1]+"!="+sv[3]+"){";
      }
      else if ((sv.size()>=1) && sv[0]=="end"){
        s1 = "}";
      }
      return s1;

    }
    void makeSTM(string filebb){
      A a;
      ifstream file(filebb);
      if (!file){
        cout<<"Can not open file";
        return;
      }
      vector<string> STM;
      string head="#include <iostream>\nusing namespace std;\nint main(){";
      STM.push_back(head);
      for (string str; getline(file, str);){
        if (a.CheckComment(str)){
          continue;
        }
        string str1="";
        if (str[str.size()-1]==13){
          for (int i=0;i<str.size()-1;i++){
              str1+=str[i];
          }
        }
        else{
          for (int i=0;i<str.size();i++){
              str1+=str[i];
          }
        }
        STM.push_back(convertBBtoCPP(str1));

      }
      string tail = "return 0;\n}";
      STM.push_back(tail);
      this->STM=STM;

    }
  public:
    string Compile(string filebb){
      makeSTM(filebb);
      A a;
      string filecpp = a.RemoveExtension(filebb)+".cpp";
      ofstream file(filecpp);
      if(!file)	{
          cout << "Khong mo duoc file.\n";
          return "";
      }
      for (int i=0;i<this->STM.size();i++){
        file<<this->STM[i]<<'\n';
      }
      file.close();
      return filecpp;
    }
};

class CppCompiler{
    public:
        void Compile(string filecpp){
            A a;
            string str = "g++ "+filecpp+" -o "+ a.RemoveExtension(filecpp);
            const char* cmd=str.c_str();
            system(cmd);
        }
    
};
int main(int argc, char** argv){
    string option = argv[1];
    if (option=="--version"){
        cout<<"BareBone Compiler (BBC) 1.0 \n Built by Diep Nguyen Tam.";
    }
    else if (option=="--g"){
      string filebb = argv[2];
      CheckSyntaxError c0;
      bool kt= c0.CheckSyntaxAllLines(filebb);
      //cout<<kt<<'\n';
      if (kt){
      BBtoCppCompiler c1;
      string filecpp = c1.Compile(filebb);
      //CppCompiler c2;
      //c2.Compile(filecpp);
      // string str = "rm "+filecpp;
      // const char* cmd=str.c_str();
      // system(cmd);
      // }
      }
    }
    else{
      string filebb = argv[1];
      CheckSyntaxError c0;
      bool kt= c0.CheckSyntaxAllLines(filebb);
      //cout<<kt<<'\n';
      if (kt){
        BBtoCppCompiler c1;
        string filecpp = c1.Compile(filebb);
        CppCompiler c2;
        c2.Compile(filecpp);
        //string str = "rm "+filecpp;
        string str = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe Remove-Item "+filecpp;
        const char* cmd=str.c_str();
        system(cmd);
      }
    }
    
    return 0;
}