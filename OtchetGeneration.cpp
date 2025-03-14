#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string language(string ways, string n, int i, string programminglanguage) {
    string line{ "" };
    fstream text(ways, ios::in | ios::out);
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
        if (programminglanguage == "o") { programminglanguage = "Arduino"; }
    }
    return programminglanguage;
}

string listing(string ways, string code, string n, int i) {
    code = "";
    string line{ "" }, line1{ "" };
    fstream text(ways, ios::in | ios::out);
    if (text.is_open()) {
        vector<string> vec;
        for (int j = 1; j <= i; j++) {
            getline(text, line);
            n = line;
        }
    }
    else {
        code = "<Сюда вставь код>";
        cout << "Не удалось открыть файл с кодом" << endl;
        return code;
    }
    text.close();
    fstream codes(n, ios::in | ios::out);
    if (codes.is_open()) {
        while (getline(codes, line1)) {
            size_t commentPos = line1.find("//");
            if (commentPos != string::npos) {
                line1 = line1.substr(0, commentPos);
            }
            code += line1 + "\n";
        }
    }
    else {
        cout << "Файл с кодами не открыт" << endl;
    }

    return code;
}

void titlePage(ofstream& file, string discipline, string numberLab, string teacher, string topic) {
    file << "\\documentclass[oneside,a4paper,14pt]{extarticle}" << endl;
    file << "\\usepackage[T1,T2A]{fontenc}" << endl;
    file << "\\usepackage[left=2.5cm,right=1.5cm,top=2cm,bottom=2cm]{geometry}" << endl;
    file << "\\usepackage[utf8]{inputenc}" << endl;
    file << "\\usepackage[russian]{babel}" << endl;
    file << "\\usepackage{textcomp}" << endl;
    file << "\\usepackage{indentfirst}" << endl;
    file << "\\usepackage{graphicx}" << endl;
    file << "\\usepackage{mwe}" << endl;
    file << "\\usepackage{wrapfig}" << endl;
    file << "\\usepackage{caption}" << endl;
    file << "\\usepackage{amsmath}" << endl;
    file << "\\usepackage{amsfonts}" << endl;
    file << "\\usepackage{amsthm}" << endl;
    file << "\\usepackage{enumitem}" << endl;
    file << "\\usepackage{minted}" << endl;
    file << "\\usepackage[all]{xy}" << endl;
    file << "\\usepackage[breaklinks]{hyperref}" << endl;
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
    file << "\\newcommand{\\solutionheading}[1] {" << endl;
    file << "    \\begin{flushleft}" << endl;
    file << "    \\hspace* {1cm}\\textbf{#1}" << endl;
    file << "    \\end{flushleft}" << endl;
    file << " }" << endl;
    file << "" << endl;
    file << "\\renewcommand\\baselinestretch{1.33}\\normalsize" << endl;
    file << "\\setlength{\\parindent}{1cm}" << endl;
    file << "\\usepackage{indentfirst}" << endl;
    file << "" << endl;
    file << "\\begin{document}" << endl;
    file << "   \\newpage\\thispagestyle{empty}" << endl;
    file << "   \\begin{center}" << endl;
    file << "\      МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ\\\\" << endl;
    file << "\      РОССИЙСКОЙ ФЕДЕРАЦИИ" << endl;
    file << "\      ФЕДЕРАЛЬНОЕ ГОСУДАРСТВЕННОЕ БЮДЖЕТНОЕ\\\\" << endl;
    file << "\      ОБРАЗОВАТЕЛЬНОЕ" << endl;
    file << "\      УЧРЕЖДЕНИЕ ВЫСШЕГО ОБРАЗОВАНИЯ\\\\" << endl;
    file << "\      «ВЯТСКИЙ ГОСУДАРСТВЕННЫЙ УНИВЕРСИТЕТ»\\\\" << endl;
    file << "\      Институт математики и информационных систем\\\\" << endl;
    file << "\      Факультет автоматики и вычислительной техники\\\\" << endl;
    file << "\      Кафедра электронных вычислительных машин" << endl;
    file << "   \\end{center}" << endl;
    file << "   \\vspace{20mm}" << endl;
    file << "" << endl;
    file << "   \\begin{center}" << endl;
    file << "   " << numberLab << endl;
    file << "   по дисциплине\\\\" << endl;
    file << "   " << discipline << "\\\\" << endl;
    file << "   <<" << topic << ">>" << endl;
    file << "\  \\end{center}" << endl;
    file << "\\vspace{48mm}" << endl;
    file << "" << endl;
    file << "\  Выполнил студент гр.ИВТб-1304-05-00 \\hspace{10mm} \\rule[-0,5mm]{30mm} {0.15mm}\\, /Ершов Н.А./" << endl;
    file << "" << endl;
    file << "" << endl;
    file << "\  Проверил старший преподаватель \\hfill\\rule[-0,5mm]{30mm} {0.15mm}\\, /" << teacher << "/" << endl;
    file << "" << endl;
    file << "\\vfill " << endl;
    file << "\  \\begin{center}" << endl;
    file << "\      Киров\\\\" << endl;
    file << "\      2025" << endl;
    file << "\  \\end{center}" << endl;
    file << "\\newpage\\thispagestyle{empty}" << endl;
}
int main(){

    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);
    int k = 0;
    int sumk = 0;
    int numberOfTasks;
    string discipline{ "" }, numberLab{ "" }, task{ "" }, programminglanguage{ "" }, teacher{ "" }, topic{ "<Сюда вставь тему>" };
    string code{ "" }, text1{ "" }, n{ "" }, report{ "" };

    cout << "Введите путь к итоговому файлу" << endl;
    cin >> report;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream file(report, ios::app);
    if (file.is_open()) {
        cout << "Выберите дисциплину (I/P/D) (I - Информатика, P - Программирование, D - Дискретная математика): ";
        cin >> discipline;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (discipline == "I") {
            discipline = "<<Информатика>>";
            teacher = "Шмакова Н. А.";
        }
        if (discipline == "P") {
            discipline = "<<Программирование>>";
            teacher = "Крутиков А. К.";
        }
        if (discipline == "D") {
            discipline = "<<Дискретная математика>>";
            teacher = "Пахарева И. В.";
        }
        cout << discipline << endl;

        cout << "Введите номер лабораторной работы: " << endl;
        cin >> numberLab;
        numberLab = "Отчёт по лабораторной работе №" + numberLab + "\\\\";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        titlePage(file, discipline, numberLab, teacher, topic);

        //file << "\\solutionheading{Цель}" << endl;
        //string purpose;
        //cout << "Введите цель Лабораторной работы: " << endl;
        //cin >> purpose;
        //cout << purpose;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        file << "" << endl;
        //file << purpose;
        int countImage = 1;

        file << "\\solutionheading{Задание}" << endl;
        cout << "Введите количество заданий: " << endl;
        cin >> numberOfTasks;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        task = "\\item";

        for (int i = 0; i < numberOfTasks; i++) {
            file << task << endl;
            file << "" << endl;
        }

        file << "" << endl;
        file << "\\newpage\\thispagestyle{empty}" << endl;
        file << "" << endl;
        file << "\\solutionheading{Задание}" << endl;
        file << "" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите путь к файлу с путями к кодам (C:/Users...)" << endl;
        string ways{ "" };
        cin >> ways;

        fstream text(ways, ios::in | ios::out);
        if (text.is_open()) {
            k = 1;
        }
        else {
            k = 0;
            cout << "не удалось открыть файл" << endl;
        }
        text.close();

        for (int i = 1; i <= numberOfTasks; i++) {
            if (i == 1) {
                file << "\\textbf{Задание  " << i << "}" << endl;
            }
            else {
                file << "\\solutionheading{Задание " << i << "}" << endl;
            }
            file << "" << endl;

            file << "\\textbf{Сюда вставь задание}" << endl;

            file << "" << endl;

            if (discipline == "<<Информатика>>") {

                int variant;

                cout << "Введите вариант работы" << endl;
                cin >> variant;

                file << "\\begin{table}[H]" << endl;

                file << "\\begin{tabular}{|l|l|l|l|}" << endl;

                file << "\\hline" << endl;

                file << "\\begin{tabular}[c]{@{}l@{}}Вариант\\ " << variant << "\\end{tabular} & \\begin{tabular}[c]{@{}l@{}}Начальное\\\\" << endl;

                file << "\\\\состояние\\end{tabular} & \\begin{tabular}[c]{@{}l@{}}Направление\\\\ движения\\end{tabular} & Пример" << endl;

                file << "\\\\ \\hline" << endl;

                file << "8 & + & \\begin{tabular}[c]{@{}l@{}}От крайних\\\\  к середине\\\\ чет/нечет\\end{tabular} & 08/26/4/35 \\\\ \\hline" << endl;

                file << "\\end{tabular}" << endl;

                file << "\\end{table}" << endl;

            }
            file << "" << endl;

            file << "\\textbf{Решение}" << endl;

            file << "\\newpage\\thispagestyle{empty}" << endl;

            if (discipline == "<<Информатика>>") {

                file << "Схема сборки представлена на рисунке " << countImage + 1 << ".Принципиальная схема представлена на рисунке " << countImage + 2 << ". Ссылка на проект : " << endl;

                file << "\\href{}{ССЫЛКА}" << endl;

                file << "\\begin{figure}[H]" << endl;
                file << "    \\centering" << endl;
                file << "    \\includegraphics[width = 1\\linewidth]{TaskMaket" << i << ".png}" << endl;
                file << "    \\caption* { Рисунок " << countImage + 1 << " - Cхема сборки на макетной плате }" << endl;
                file << "        \\label{ fig:enter - label }" << endl;
                file << "\\end{figure}" << endl;
                file << "" << endl;

                file << "\\begin{figure}[H]" << endl;
                file << "    \\centering" << endl;
                file << "    \\includegraphics[width = 1\\linewidth]{TaskPrinc" << i << ".png}" << endl;
                file << "    \\caption* { Рисунок " << countImage + 2 << " - Принципиальная схема }" << endl;
                file << "        \\label{ fig:enter - label }" << endl;
                file << "\\end{figure}" << endl;
                file << "" << endl;

                countImage += 2;
            }

            file << "" << endl;

            file << "\\linespread{1}" << endl;

            file << "" << endl;

            code = listing(ways, code, n, i);

            programminglanguage = language(ways, n, i, programminglanguage);

            file << "\\textbf{Решение на языке программирования " << "<<";
            
            if (discipline == "<<Информатика>>") {file << "C++ " + programminglanguage << ">>" << "}" << endl; }//ардуино
            else { file << programminglanguage << ">>" << "}" << endl; }

            file << "\\begin{minted}[linenos=true]{" << programminglanguage << "}" << endl;

            file << code << endl;

            file << "\\end{minted}" << endl;

            file << "" << endl;

            file << "\\newpage\\thispagestyle{empty}" << endl;

            file << "" << endl;
        }
        file << "\\solutionheading{Вывод}" << endl;
        file << "" << endl;
        file << "<Сюда вставь вывод>" << endl;
        file << "" << endl;
        file << "\\end{document}" << endl;

        file.close();
    }
    else {
        cout << "Не удалось открыть итоговый файл";
        return 0;
    }
    cout << "Отчет сформирован" << endl;
    return 0;
}
