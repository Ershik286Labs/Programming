#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string language(string ways, string n, int i, string programminglanguage) {
    string line{ "" };
    fstream text(ways, ios::in | ios::out); //������������ ���������� � �����
    if (text.is_open()) {
        vector<string> vec;
        for (int j = 1; j <= i; j++) {
            getline(text, line);
            n = line;
        }
        programminglanguage = n.back();
        if (programminglanguage == "s") {
            programminglanguage = "Pascal";
        }
        if (programminglanguage == "c") {
            programminglanguage = "C";
        }
        if (programminglanguage == "p") {
            programminglanguage = "C++";
        }
        if (programminglanguage == "a") {
            programminglanguage = "Java";
        }
    }
    return programminglanguage;
}

string listing(string ways, string code, string n, int i) {
    code = "";
    string line{ "" }, line1{ "" };
    fstream text(ways, ios::in | ios::out); //������������ ���������� � �����
    if (text.is_open()) {
        vector<string> vec;
        for (int j = 1; j <= i; j++) {
            getline(text, line);
            n = line;
        }
    }
    else {
        code = "<���� ������ ���>";
        cout << "�� ������� ������� ���� � ������" << endl;
        return code;
    }
    text.close();
    fstream codes(n, ios::in | ios::out); //������������ ���������� � �����
    if (codes.is_open()) {
        while (getline(codes, line1)) {
            size_t commentPos = line1.find("//"); // ���� ������� �����������
            if (commentPos != string::npos) {
                line1 = line1.substr(0, commentPos); // �������� ������ �� �����������
            }
            code += line1 + "\n"; // ��������� ������ � code
        }
    }
    else {
        cout << "�� ������� ������� ���� � ���������" << endl;
    }

    return code;
}

void titlePage(ofstream& file, string discipline, string numberLab, string teacher, string topic) {
    file << "\\documentclass[oneside,a4paper,14pt]{extarticle} %������ ������ 14" << endl;
    file << "\\usepackage[T1,T2A]{fontenc}" << endl;
    file << "\\usepackage[left=2.5cm,right=1.5cm,top=2cm,bottom=2cm]{geometry}" << endl;
    file << "\\usepackage[utf8]{inputenc} % ��������� ������" << endl;
    file << "\\usepackage[russian]{babel} % ��������� �������� �����" << endl;
    file << "\\usepackage{textcomp} % ��������� �������" << endl;
    file << "\\usepackage{indentfirst} % ������������� ��������" << endl;
    file << "\\usepackage{graphicx} % ������ � ������������" << endl;
    file << "\\usepackage{mwe} % for blindtext and example - image - a in example" << endl;
    file << "\\usepackage{wrapfig}" << endl;
    file << "\\usepackage{caption}" << endl;
    file << "\\usepackage{amsmath} % ��� ������ � ��������" << endl;
    file << "\\usepackage{amsfonts}" << endl;
    file << "\\usepackage{amsthm}" << endl;
    file << "\\usepackage{enumitem}" << endl;
    file << "\\usepackage{minted}" << endl;
    file << "\\usepackage[all]{xy}" << endl;
    file << "\\usepackage[breaklinks]{hyperref}" << endl;
    file << " % %�����������������������������" << endl;
    file << "\\usepackage{titlesec}" << endl;
    file << "\\titleformat{\\section}" << endl;
    file << "\{\\normalsize\\bfseries}" << endl;
    file << "\{\\thesection} {1em} {}" << endl;
    file << "     \\titleformat{\subsection}" << endl;
    file << "{\\normalsize\\bfseries}" << endl;
    file << " {\\thesubsection} {1em} {}" << endl;
    file << "    \\titleformat{\\subsubsection}" << endl;
    file << "{\\normalsize\\bfseries}" << endl;
    file << "{\\thesubsection} {1em} {}" << endl;
    file << "" << endl;
    file << "\\newcommand{\\solutionheading}[1] {% ��������� �������" << endl;
    file << "    \\begin{flushleft}" << endl;
    file << "    \\hspace* {1.25cm}\\textbf{#1}" << endl;
    file << "    \\end{flushleft}" << endl;
    file << "    \\vspace{0.5cm}" << endl;
    file << " }" << endl;
    file << "" << endl;
    file << "\\renewcommand\\baselinestretch{1.33}\\normalsize% ����������� ��������" << endl;
    file << "\\setlength{\\parindent}{1.25cm}" << endl;
    file << "\\usepackage{indentfirst}" << endl;
    file << "" << endl;
    file << "\\begin{document}" << endl;
    file << "   \\newpage\\thispagestyle{empty}" << endl;
    file << "   \\begin{center}" << endl;
    file << "\      ������������ ����� � ������� �����������\\\\" << endl;
    file << "\      ���������� ���������" << endl;
    file << "\      ����������� ��������������� ���������\\\\" << endl;
    file << "\      ���������������" << endl;
    file << "\      ���������� ������� �����������\\\\" << endl;
    file << "\      �������� ��������������� ����������һ\\\\" << endl;
    file << "\      �������� ���������� � �������������� ������\\\\" << endl;
    file << "\      ��������� ���������� � �������������� �������\\\\" << endl;
    file << "\      ������� ����������� �������������� �����" << endl;
    file << "   \\end{center}" << endl;
    file << "   \\vspace{20mm}" << endl;
    file << "" << endl;
    file << "   \\begin{center}" << endl;
    file << "   " << numberLab << endl;
    file << "   �� ����������\\\\" << endl;
    file << "   " << discipline << "\\\\" << endl;
    file << "   " << topic << endl; //���� �� ��������, ��� ��� �� �������� ������ ���� � ������� :(
    file << "\  \\end{center}" << endl;
    file << "\\vspace{48mm}" << endl;
    file << "" << endl;
    file << "\  �������� ������� ��.����-1304-05-00 \\hspace{10mm} \\rule[-0,5mm]{30mm} {0.15mm}\\, /����� �.�./" << endl;
    file << "" << endl;
    file << "" << endl;
    file << "\  �������� ������� ������������� \\hfill\\rule[-0,5mm]{30mm} {0.15mm}\\, /" << teacher << "/" << endl;
    file << "" << endl;
    file << "\\vfill " << endl;
    file << "\  \\begin{center}" << endl;
    file << "\      �����\\\\" << endl;
    file << "\      2024" << endl;
    file << "\  \\end{center}" << endl;
    file << "\\newpage\\thispagestyle{empty}" << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int k = 0;
    int sumk = 0; //����� ����� ����� �����
    int numberOfTasks;
    string discipline{ "" }, numberLab{ "" }, task{ "" }, programminglanguage{ "" }, teacher{ "" }, topic{ "<���� ����� ����>" };
    string code{ "" }, text1{ "" }, n{ "" }, report{ "" };

    cout << "������� ���� � ����� � �������:" << endl;
    cin >> report;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream file(report, ios::app);
    if (file.is_open()) {
        cout << "������� ���������� (I/P/Cult) (I - �����������, P - ����������������, Cult - ���): "; //����������
        cin >> discipline;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (discipline == "I") {
            discipline = "�����������";
            teacher = "������� �. �.";
        }
        if (discipline == "P") {
            discipline = "����������������";
            teacher = "�������� �. �.";
        }
        if (discipline == "Cult") {
            discipline = "������ ���������� ��������";
            teacher = "�������� �. �.";
        }
        cout << discipline << endl;

        cout << "������� ����� ������������ ������: " << endl;//����� ������
        cin >> numberLab;
        numberLab = "����� �� ������������ ������ �" + numberLab + "\\\\";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        titlePage(file, discipline, numberLab, teacher, topic);

        file << "\\solutionheading{����}" << endl;
        file << "<���� ����� ����>" << endl;

        //�������� �������
        file << "\\solutionheading{�������}" << endl;
        cout << "������� ���-�� �������: " << endl;
        cin >> numberOfTasks;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < numberOfTasks; i++) { //���� ����, ���� �� �������� ���-�� �������
            file << "\\textbf{������� " << i << "}" << endl;
            file << task << endl;
        }

        //��������� �������
        file << "" << endl;
        file << "\\newpage\\thispagestyle{empty}" << endl;
        file << "\\solutionheading{�������}" << endl;
        file << "" << endl;

        cout << "������� ������ �� ���� � ������ (C:/Users...) !��� ���������)" << endl;
        string ways{ "" };
        cin >> ways;

        fstream text(ways, ios::in | ios::out); //������������ ���������� � �����
        if (text.is_open()) {
            k = 1;
        }
        else {
            k = 0;
            cout << "�� ������� ������� ���� � ������" << endl;
        }
        text.close();

        for (int i = 1; i <= numberOfTasks; i++) {
            if (i == 1) {
                file << "\\textbf{������� " << i << "}" << endl;
            }
            else {
                file << "\\solutionheading{������� " << i << "}" << endl;
            }
            file << "" << endl;
            file << "\\textbf{���� �������}" << endl;

            file << "" << endl;
            file << "\\textbf{�� �����:}\\\\" << endl;
            file << "" << endl;
            file << "\\textbf{�� ������:}\\\\" << endl;
            file << "" << endl;
            file << "\\textbf{�������:}\\\\" << endl;

            file << "" << endl;

            file << "\\textbf{���������� ������� ������: }" << endl;

            file << "" << endl;

            file << "\\linespread{1}" << endl;

            file << "" << endl;

            code = listing(ways, code, n, i);

            programminglanguage = language(ways, n, i, programminglanguage);

            file << "\\newpage\\thispagestyle{empty}" << endl;

            file << "" << endl;

            file << "<����� �������� �� ������>" << endl;

            file << "" << endl;

            file << "\\newpage\\thispagestyle{empty}" << endl;

            file << "\\textbf{������� �� �����" << "<<" << programminglanguage << ">>" << "}" << endl;

            file << "\\begin{minted}[linenos=true]{" << programminglanguage << "}" << endl;

            file << code << endl;

            file << "\\end{minted}" << endl;

            file << "" << endl;
        }
        file << "\\solutionheading{�����}" << endl;
        file << "<����� �����>" << endl;
        file << "\\end{document}" << endl;

        file.close();
    }
    else {
        cout << "�� ������� ������� ����, ���������� �����.";
        return 0;
    }
    cout << "����� �����������" << endl;
    return 0;
}