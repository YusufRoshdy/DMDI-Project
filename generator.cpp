#include <bits/stdc++.h>

using namespace std;

struct doctor
{
        int d_id;
        string first_name;
        string last_name;
        string birth_date;
        string joined_date;
        int salary;
        string email;
}doctor_e;
vector < doctor > doctors;

struct patient
{
	int p_id;
	string first_name;
	string last_name;
	string date_of_birth;
	int gender;
	int medical_history;
	string email;
}patient_e;
vector < patient > patients;

struct appointment
{
        int d_id;
        int n_id;
        string time_slot;
        int p_id;
}appointment_e;
vector < appointment > appointments;

struct wards_assigned
{
        int p_id;
        int w_id;
        string start_date;
        string end_date;
}wards_assigned_e;
vector < wards_assigned > wardsassigned;

struct prescription
{
        int d_id;
        int p_id;
        int drug_id;
        string date;
        string end_date;
        int pr_id;
}prescription_e;
vector < prescription > prescriptions;

struct assigned_nurse
{
        int n_id;
        int p_id;
}assigned_nurse_e;
vector < assigned_nurse > assigned_nurses;

struct janitor_ward
{
        int j_id;
        int w_id;
        string date;
}janitor_ward_e;
vector < janitor_ward > janitor_wards;

struct attend_patient
{
        int d_id;
        int w_id;
        string date;
}attend_patient_e;
vector < attend_patient > attend_patients;

struct buy
{
        int p_id;
        int pr_id;
        string date;
}buy_e;
vector < buy > buys;

struct nurse
{
        int n_id;
        string first_name;
        string last_name;
        string birth_date;
        string joined_date;
        int salary;
        string email;
        int d_id;
}nurse_e;
vector < nurse > nurses;

struct staff
{
        int s_id;
        string first_name;
        string last_name;
        string birth_date;
        string joined_date;
        int salary;
        string position;
        string email;
}staff_e;
vector < staff > staffs;

struct ward
{
        int w_id;
        int number_of_beds;
}ward_e;
vector < ward > wards;

struct medical_card
{
        int card_id;
        int blood_type;
        int rh_factor;
        string chronic_disiases;
        string vaccinations;
}medical_card_e;
vector < medical_card > medical_cards;

struct drug
{
        string commercial_name;
        string international_nonproprietary_name;
        int amount;
        int price;
}drug_e;
vector < drug > drugs;

struct wards_nurse
{
        int w_id;
        int n_id;
        string date;
}wards_nurse_e;
vector < wards_nurse > wards_nurses;

string int_to_string(int x)
{
        string res = "";
        while(x > 0){
                res += char(x % 10 + '0');
                x /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
}

string fill_full(string s, int need)
{
        while(s.size() < need){
                s = "0" + s;
        }
        return s;
}

string random_date(int year_l, int year_r)
{
        string res = "";

        res += int_to_string(rand() % (year_r - year_l + 1) + year_l);
        res += "-";
        res += fill_full(int_to_string(rand() % 12 + 1), 2);
        res += "-";
        res += fill_full(int_to_string(rand() % 28 + 1), 2);
        res += " ";
        res += fill_full(int_to_string(rand() % 24), 2);
        res += ":";
        res += fill_full(int_to_string(rand() % 60), 2);
        res += ":";
        res += fill_full(int_to_string(rand() % 60), 2);
        res += ".";
        res += fill_full(int_to_string(rand() % 100000), 5);

        return res;
}

string random_date2(int year_l, int year_r)
{
        string res = "";

        res += int_to_string(rand() % (year_r - year_l + 1) + year_l);
        res += "-";
        res += fill_full(int_to_string(rand() % 12 + 1), 2);
        res += "-";
        res += fill_full(int_to_string(rand() % 28 + 1), 2);

        return res;
}

string random_email(string name, string surname)
{
        string res = "";
        if(rand() & 1){
                res += name[0];
        } else{
                res += name;
        }
        if(rand() & 1){
                res += ".";
        }
        res += surname;
        res += fill_full(int_to_string(rand() % 381), rand() % 3 + 1);

        vector < string > tp = {"@gmail.com", "@mail.ru", "@innopolis.university", "@yandex.ru", "@farhod.club"};

        res += tp[rand() % int(tp.size())];

        return res;
}

int main()
{
        FILE *name_file = fopen("Name and Surnames.txt", "r");

        vector < string > name, surname;
        string s = "";
        while(!feof(name_file)){
                char c = getc(name_file);
                if(c == ' '){
                        name.push_back(s);
                        s = "";
                } else if(c == '\n'){
                        surname.push_back(s);
                        s = "";

                        bool good = true;
                        for(char x: name.back()){
                                if((x < 'a' || x > 'z') && (x < 'A' || x > 'Z')){
                                        good = false;
                                }
                        }
                        for(char x: surname.back()){
                                if((x < 'a' || x > 'z') && (x < 'A' || x > 'Z')){
                                        good = false;
                                }
                        }
                        if(good == false){
                                name.pop_back();
                                surname.pop_back();
                        }
                } else{
                        s += c;
                }
        }
        if(!s.empty()){
                surname.push_back(s);
        }
        bool good = true;
        for(char x: name.back()){
                if((x < 'a' || x > 'z') && (x < 'A' || x > 'Z')){
                        good = false;
                }
        }
        for(char x: surname.back()){
                if((x < 'a' || x > 'z') && (x < 'A' || x > 'Z')){
                        good = false;
                }
        }
        if(good == false){
                name.pop_back();
                surname.pop_back();
        }
        freopen("output.txt", "wb", stdout);



        // doctors
        for(int i = 0; i < 30; i++){
                doctors.push_back(doctor_e);
                doctors.back().d_id = i;
                doctors.back().first_name = name.back();
                doctors.back().last_name = surname.back();
                name.pop_back();
                surname.pop_back();
                doctors.back().birth_date = random_date2(1950, 1980);
                doctors.back().joined_date = random_date(2004, 2019);
                doctors.back().salary = (rand() % 100 + 1) * 10000;
                doctors.back().email = random_email(doctors.back().first_name, doctors.back().last_name);

                cout << "INSERT INTO doctors (first_name, last_name, birth_date, joined_date, salary, email) VALUES (";
                cout << "'" << doctors.back().first_name << "'" << ", ";
                cout << "'" << doctors.back().last_name << "', ";
                cout << "'" << doctors.back().birth_date << "', ";
                cout << "'" << doctors.back().joined_date << "', ";
                cout << doctors.back().salary << ", ";
                cout << "'" << doctors.back().email << "');\n";


        }

        // patients
        for(int i = 0; i < 50; i++){
                patients.push_back(patient_e);
                patients.back().p_id = i;
                patients.back().first_name = name.back();
                patients.back().last_name = surname.back();
                name.pop_back();
                surname.pop_back();
                patients.back().date_of_birth = random_date2(1950, 2014);
                patients.back().gender = rand() % 2;
                patients.back().medical_history = rand() % 30;
                patients.back().email = random_email(patients.back().first_name, patients.back().last_name);

                cout << "INSERT INTO patients (first_name, last_name, date_of_birth, gender, medical_history, email) VALUES (";
                cout << "'" << patients.back().first_name << "'" << ", ";
                cout << "'" << patients.back().last_name << "'" << ", ";
                cout << "'" << patients.back().date_of_birth << "', ";
                cout << patients.back().gender << ", ";
                cout << patients.back().medical_history << ", ";
                cout << "'" << patients.back().email << "');\n";



        }

        // appointments
        set < pair < int, string > > app_used;
        for(int i = 0; i < 1000; i++){

                appointments.push_back(appointment_e);
                appointments.back().d_id = rand() % int(doctors.size());
                appointments.back().time_slot = random_date(2010, 2019);
                appointments.back().p_id = rand() % int(patients.size());
                appointments.back().n_id = rand() % int(30);

                string &s = appointments.back().time_slot;
                int g = s.size();
                s[g - 1] = s[g - 2] = s[g - 3] = s[g - 4] = s[g - 5] = '0';
                s[g - 7] = s[g - 8] = '0';
                s[g - 10] = s[g - 11] = '0';

                s[g - 14] = '1';
                s[g - 13] = '0';
                s[g - 13] += rand() % 3;
                if(app_used.find({appointments.back().d_id, appointments.back().time_slot}) != app_used.end()){
                        appointments.pop_back();
                        continue;
                }
                app_used.insert({appointments.back().d_id, appointments.back().time_slot});


                cout << "INSERT INTO appointments (n_id, d_id, time_slot, p_id) VALUES (";
                cout << appointments.back().n_id << ", ";
                cout << appointments.back().d_id << ", ";
                cout << "'" << appointments.back().time_slot << "'" << ", ";
                cout << appointments.back().p_id << ");" << "\n";


        }

        for(int i = 0; i < 1000; i++){

                appointments.push_back(appointment_e);
                appointments.back().d_id = rand() % int(doctors.size());
                appointments.back().time_slot = random_date(2018, 2019);
                appointments.back().p_id = rand() % int(patients.size());
                appointments.back().n_id = rand() % int(30);

                string &s = appointments.back().time_slot;
                int g = s.size();
                s[g - 1] = s[g - 2] = s[g - 3] = s[g - 4] = s[g - 5] = '0';
                s[g - 7] = s[g - 8] = '0';
                s[g - 10] = s[g - 11] = '0';

                s[g - 14] = '1';
                s[g - 13] = '0';
                s[g - 13] += rand() % 3;
                if(app_used.find({appointments.back().d_id, appointments.back().time_slot}) != app_used.end()){
                        appointments.pop_back();
                        continue;
                }
                app_used.insert({appointments.back().d_id, appointments.back().time_slot});


                cout << "INSERT INTO appointments (n_id, d_id, time_slot, p_id) VALUES (";
                cout << appointments.back().n_id << ", ";
                cout << appointments.back().d_id << ", ";
                cout << "'" << appointments.back().time_slot << "'" << ", ";
                cout << appointments.back().p_id << ");" << "\n";


        }

        // wards_assigned

        for(int i = 0; i < 80; i++){
                wardsassigned.push_back(wards_assigned_e);
                wardsassigned.back().p_id = rand() % int(patients.size());
                wardsassigned.back().w_id = rand() % 40;
                int year = rand() % 10 + 2010;
                wardsassigned.back().start_date = random_date2(year, year);
                wardsassigned.back().end_date = random_date2(year, year);
                if(wardsassigned.back().start_date > wardsassigned.back().end_date){
                        swap(wardsassigned.back().start_date, wardsassigned.back().end_date);
                }

                cout << "INSERT INTO wards_assigned (p_id, w_id, start_date, end_date) VALUES (";
                cout << wardsassigned.back().p_id << ", ";
                cout << wardsassigned.back().w_id << ", ";
                cout << "'" << wardsassigned.back().start_date << "', ";
                cout << "'" << wardsassigned.back().end_date << "');" << "\n";
        }

        // prescription
        for(int i = 0; i < 30; i++){
                prescriptions.push_back(prescription_e);
                prescriptions.back().d_id = rand() % int(doctors.size());
                prescriptions.back().p_id = rand() % int(patients.size());
                prescriptions.back().drug_id = rand() % 30;
                prescriptions.back().date = random_date2(2018, 2019);
                //prescriptions.back().pr_id = rand() % 30;

                cout << "INSERT INTO prescriptions (d_id, p_id, drug_id, date) VALUES (";
                cout << prescriptions.back().d_id << ", ";
                cout << prescriptions.back().p_id << ", ";
                cout << prescriptions.back().drug_id << ", ";
                cout << "'" << prescriptions.back().date << "');\n";
        }

        // assigned_nurses
        /*
        for(int i = 0; i < 30; i++){
                assigned_nurses.push_back(assigned_nurse_e);
                assigned_nurses.back().n_id = rand() % 30;
                assigned_nurses.back().p_id = rand() % int(patients.size());

                cout << "INSERT INTO assigned_nurses (n_id, p_id) VALUES (";
                cout << assigned_nurses.back().n_id << ", ";
                cout << assigned_nurses.back().p_id << ");\n";
        }
        */

        // janitor_wards
        for(int i = 0; i < 30; i++){
                janitor_wards.push_back(janitor_ward_e);
                janitor_wards.back().j_id = rand() % 30;
                janitor_wards.back().w_id = rand() % 30;
                janitor_wards.back().date = random_date2(2018, 2019);

                cout << "INSERT INTO janitor_wards (j_id, w_id, date) VALUES (";
                cout << janitor_wards.back().j_id << ", ";
                cout << janitor_wards.back().w_id << ", ";
                cout << "'" << janitor_wards.back().date << "');\n";
        }

        // attend_patients
        for(int i = 0; i < 30; i++){
                attend_patients.push_back(attend_patient_e);
                attend_patients.back().d_id = rand() % int(doctors.size());
                attend_patients.back().w_id = rand() % 30;
                attend_patients.back().date = random_date2(2018, 2019);

                cout << "INSERT INTO attend_patients (d_id, w_id, date) VALUES (";
                cout << attend_patients.back().d_id << ", ";
                cout << attend_patients.back().w_id << ", ";
                cout << "'" << attend_patients.back().date << "');\n";
        }

        // buy
        for(int i = 0; i < 30; i++){
                buys.push_back(buy_e);
                //buys.back().p_id = rand() % int(patients.size());
                buys.back().pr_id = rand() % 30;
                buys.back().date = random_date2(2018, 2019);

                cout << "INSERT INTO buy (pr_id, date) VALUES (";
                //cout << buys.back().p_id << ", ";
                cout << buys.back().pr_id << ", ";
                cout << "'" << buys.back().date << "');\n";
        }

        // nurses
        for(int i = 0; i < 30; i++){
                nurses.push_back(nurse_e);
                nurses.back().first_name = name.back();
                nurses.back().last_name = surname.back();
                name.pop_back();
                surname.pop_back();
                nurses.back().birth_date = random_date2(1950, 1990);
                nurses.back().joined_date = random_date(2004, 2019);
                nurses.back().salary = (rand() % 100 + 1) * 100;
                nurses.back().d_id = rand() % int(doctors.size());
                nurses.back().email = random_email(nurses.back().first_name, nurses.back().last_name);

                cout << "INSERT INTO nurses (first_name, last_name, birth_date, joined_date, salary, d_id, email) VALUES (";
                cout << "'" << nurses.back().first_name << "', ";
                cout << "'" << nurses.back().last_name << "', ";
                cout << "'" << nurses.back().birth_date << "', ";
                cout << "'" << nurses.back().joined_date << "', ";
                cout << nurses.back().salary << ", ";
                cout << nurses.back().d_id << ", ";
                cout << "'" << nurses.back().email << "');\n";
        }

        //staff
        vector < string > positions = {"Chef", "Manager", "Janitor"};
        vector < int > expected_salary {100, 500, 20};
        for(int i = 0; i < 30; i++){
                staffs.push_back(staff_e);
                staffs.back().first_name = name.back();
                staffs.back().last_name = surname.back();
                name.pop_back();
                surname.pop_back();
                staffs.back().birth_date = random_date2(1950, 1980);
                staffs.back().joined_date = random_date2(2004, 2019);
                int tp = rand() % int(positions.size());
                staffs.back().position = positions[tp];
                staffs.back().salary = (rand() % 100 + 1) * expected_salary[tp];
                staffs.back().email = random_email(staffs.back().first_name, staffs.back().last_name);

                cout << "INSERT INTO staff (first_name, last_name, birth_date, joined_date, position, salary, email) VALUES (";
                cout << "'" << staffs.back().first_name << "', ";
                cout << "'" << staffs.back().last_name << "', ";
                cout << "'" << staffs.back().birth_date << "', ";
                cout << "'" << staffs.back().joined_date << "', ";
                cout << "'" << staffs.back().position << "', ";
                cout << staffs.back().salary << ", ";
                cout << "'" << staffs.back().email << "');\n";
        }

        //wards
        for(int i = 0; i < 30; i++){
                wards.push_back(ward_e);
                wards.back().number_of_beds = rand() % 6 + 1;

                cout << "INSERT INTO wards (number_of_beds) VALUES (";
                cout << wards.back().number_of_beds << ");\n";
        }

        //medical_cards
        for(int i = 0; i < 30; i++){
                medical_cards.push_back(medical_card_e);
                medical_cards.back().blood_type = rand() % 4 + 1;
                medical_cards.back().rh_factor = (rand() & 1 ? 1 : -1);

                cout << "INSERT INTO medical_cards (blood_type, rh_factor, chronic_disiases, vaccinations) VALUES (";
                cout << medical_cards.back().blood_type << ", ";
                cout << medical_cards.back().rh_factor << ", ";
                cout << "'', ";
                cout << "'');\n";
        }

        //drugs
        for(int i = 0; i < 7; i++){
                drugs.push_back(drug_e);
                drugs.back().amount = rand();
                drugs.back().price = (rand() % 10 + 1) * 23;
                if(i == 0){
                        drugs.back().commercial_name = "Altace";
                        drugs.back().international_nonproprietary_name = "ramipril";
                } else if(i == 2){
                        drugs.back().commercial_name = "Amaryl";
                        drugs.back().international_nonproprietary_name = "glimepiride";
                } else if(i == 3){
                        drugs.back().commercial_name = "Ambien";
                        drugs.back().international_nonproprietary_name = "zolpidem";
                } else if(i == 4){
                        drugs.back().commercial_name = "Ativan";
                        drugs.back().international_nonproprietary_name = "lorazepam";
                } else if(i == 5){
                        drugs.back().commercial_name = "Mevacor";
                        drugs.back().international_nonproprietary_name = "lovastatin";
                } else if(i == 6){
                        drugs.back().commercial_name = "Prilosec";
                        drugs.back().international_nonproprietary_name = "omeprazole";
                } else if(i == 1){
                        drugs.back().commercial_name = "Synthroid";
                        drugs.back().international_nonproprietary_name = "levothyroxine";
                }

                cout << "INSERT INTO drugs (price, commercial_name, international_nonproprietary_name, amount) VALUES (";
                cout << drugs.back().price << ", ";
                cout << "'" << drugs.back().commercial_name << "', ";
                cout << "'" << drugs.back().international_nonproprietary_name << "', ";
                cout << drugs.back().amount << ");\n";
        }

        //wards_nurses
        set < pair < int, string > > ward_used;
        for(int i = 0; i < 30; i++){
                wards_nurses.push_back(wards_nurse_e);
                wards_nurses.back().w_id = rand() % (int)wards.size();
                wards_nurses.back().n_id = rand() % (int)nurses.size();
                wards_nurses.back().date = random_date2(2019, 2019);
                if(ward_used.find({wards_nurses.back().w_id, wards_nurses.back().date}) != ward_used.end()){
                        continue;
                }
                ward_used.insert({wards_nurses.back().w_id, wards_nurses.back().date});

                cout << "INSERT INTO wards_nurses (w_id, n_id, date) VALUES (";
                cout << wards_nurses.back().w_id << ", ";
                cout << wards_nurses.back().n_id << ", ";
                cout << "'" << wards_nurses.back().date << "');\n";
        }
}
