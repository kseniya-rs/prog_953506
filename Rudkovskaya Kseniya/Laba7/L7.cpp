#include <iostream>
#include <time.h>
#define LONG_STR 256

const char* hrdfilename = "D:\\Си\\L7\\Emploeyes.txt";

int GetUserMenuInput() {
	char line[20];
	gets_s(line, sizeof(line));
	int i;
	if (sscanf_s(line, "%d", &i) == 1)
		return i;
	return 0;
}

char GetUserMenuInputChar() {
	char line[20];
	gets_s(line, sizeof(line));
	char i;
	if (sscanf_s(line, "%c", &i) == 1)
		return i;
	return 0;
}

struct Emploeye {
	char surname[20];
	char name[20];
	char fathersname[20];
	struct tm birthday;
	char pasportdata[10];
	char socprotectcard[20];
	char education[LONG_STR];
	char position[20];
	float salary;
	struct tm startday;
	char coments[LONG_STR];
};

void InitializeEmploeye(Emploeye* emploeye) {
	memset(emploeye, 0, sizeof(Emploeye));
}

struct HumanResourcesDepartment {
	int totalpersons;
	Emploeye* persons;

};

void SetTm(struct tm& tm, int year, int month, int day) {
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
}

Emploeye* SetBirthday(Emploeye* person, int year, int month, int day) {
	if (person) {
		SetTm(person->birthday, year, month, day);
	}
	return person;
}

Emploeye* SetStartDay(Emploeye* person, int year, int month, int day) {
	if (person) {
		SetTm(person->startday, year, month, day);
	}
	return person;
}

time_t CreateNoticeLimit(int days) {
	__time32_t curtime = time(0);
	__time32_t limit = curtime + (days * 24 * 60 * 60);
	struct tm lim;
	_localtime32_s(&lim, &limit);
	lim.tm_hour = 0;
	lim.tm_min = 0;
	lim.tm_sec = 0;
	return mktime(&lim);
}

HumanResourcesDepartment* LoadHRD(const char* filename) {
	HumanResourcesDepartment* hrd = (HumanResourcesDepartment*)malloc(sizeof(HumanResourcesDepartment));
	hrd->totalpersons = 0;
	hrd->persons = NULL;

	FILE* file;
	if (fopen_s(&file, filename, "r")) {
		printf("Warning! HRD database file %s not found. Creating empty database.\n", hrdfilename);
		return hrd;
	}
	char line[LONG_STR];
	fgets(line, sizeof(line), file);

	if (sscanf_s(line, "%d", &hrd->totalpersons) != 1) {
		printf("Error! Could not read persons count.");
		exit(EXIT_FAILURE);
	}
	hrd->persons = (Emploeye*)malloc(hrd->totalpersons * sizeof(Emploeye));
	if (hrd->persons == NULL) {
		printf("Error! Could not allocate memory for HRD database.");
		exit(EXIT_FAILURE);
	}
	const char* delimiters = ",\n";
	for (int i = 0; i < hrd->totalpersons; i++) {

		fgets(line, sizeof(line), file);
		char* word = line;
		char* context = NULL;

		InitializeEmploeye(&hrd->persons[i]);
		word = strtok_s(line, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].surname, word, sizeof(hrd->persons->surname));
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].name, word, sizeof(hrd->persons->name));
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].fathersname, word, sizeof(hrd->persons->fathersname));
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].birthday.tm_year);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].birthday.tm_mon);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].birthday.tm_mday);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].pasportdata, word, sizeof(hrd->persons->pasportdata));
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].socprotectcard, word, sizeof(hrd->persons->socprotectcard));
		}
		fgets(line, sizeof(line), file);
		word = strtok_s(line, "\n", &context);
		if (word) {
			strncpy_s(hrd->persons[i].education, word, sizeof(hrd->persons->education));
		}
		fgets(line, sizeof(line), file);

		word = strtok_s(line, delimiters, &context);
		if (word) {
			strncpy_s(hrd->persons[i].position, word, sizeof(hrd->persons->position));
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%f", &hrd->persons[i].salary);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].startday.tm_year);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].startday.tm_mon);
		}
		word = strtok_s(NULL, delimiters, &context);
		if (word) {
			sscanf_s(word, "%d", &hrd->persons[i].startday.tm_mday);
		}
		fgets(line, sizeof(line), file);
		word = strtok_s(line, "\n", &context);
		if (word) {
			strncpy_s(hrd->persons[i].coments, word, sizeof(hrd->persons->coments));
		}

	}
	fclose(file);
	return hrd;
}

int SaveHRD(HumanResourcesDepartment* hrd, const char* filename) {
	FILE* file;
	if (!fopen_s(&file, filename, "w")) {

		fprintf(file, "%d\n", hrd->totalpersons);
		for (int i = 0; i < hrd->totalpersons; i++) {
			Emploeye& person = hrd->persons[i];
			fprintf(file, "%s,%s,%s,", person.surname, person.name, person.fathersname);
			fprintf(file, "%d,%d,%d,", person.birthday.tm_year, person.birthday.tm_mon, person.birthday.tm_mday);
			fprintf(file, "%s,%s,\n", person.pasportdata, person.socprotectcard);
			fprintf(file, "%s\n", person.education);
			fprintf(file, "%s,%.2f,%d,%d,%d,\n", person.position, person.salary, person.startday.tm_year, person.startday.tm_mon, person.startday.tm_mday);
			fprintf(file, "%s\n", person.coments);
		}
		fclose(file);
		return 1;
	}
	return 0;

}

void PrintEmployeInfoShort(Emploeye* person) {
	printf("Surname: %s, Name: %s, Fathersname: %s, ", person->surname, person->name, person->fathersname);
	printf("Birthday: %d.%d.%d\n", person->birthday.tm_year + 1900, person->birthday.tm_mon + 1, person->birthday.tm_mday);
	printf("Position: %s, Salary: %.2f, Works since: %d.%d.%d\n", person->position, person->salary, person->startday.tm_year + 1900, person->startday.tm_mon + 1, person->startday.tm_mday);
}

void PrintEmployesInfoShort(HumanResourcesDepartment* hrd) {
	for (int i = 0; i < hrd->totalpersons; i++) {
		printf("%d: ", i + 1);
		PrintEmployeInfoShort(hrd->persons + i);
	}
}

void PrintEmploeyesFullInfo(Emploeye* person) {
	printf("Surname: %s, Name: %s, Fathersname: %s,\n", person->surname, person->name, person->fathersname);
	printf("Birthday: %d.%d.%d\n", person->birthday.tm_year + 1900, person->birthday.tm_mon + 1, person->birthday.tm_mday);
	printf("Pasport: %s, SocCard: %s,\n", person->pasportdata, person->socprotectcard);
	printf("Education: %s\n", person->education);
	printf("Position: %s, Salary: %.2f, Works since: %d.%d.%d\n", person->position, person->salary, person->startday.tm_year + 1900, person->startday.tm_mon + 1, person->startday.tm_mday);
	printf("%s\n", person->coments);
}


Emploeye* AddNewEmploeyeShort(HumanResourcesDepartment* hrd) {
	Emploeye person;
	InitializeEmploeye(&person);
	printf("Enter the surname: ");
	scanf_s("%s", &person.surname, sizeof(person.surname));
	printf("Enter the name: ");
	scanf_s("%s", &person.name, sizeof(person.name));
	printf("Enter the fathersname: ");
	scanf_s("%s", &person.fathersname, sizeof(person.fathersname));
	printf("Enter the birthday:\n");
	printf("Enter the year of birth:");
	scanf_s("%d", &person.birthday.tm_year);
	person.birthday.tm_year -= 1900;
	printf("Enter the month of birth: ");
	scanf_s("%d", &person.birthday.tm_mon);
	person.birthday.tm_mon -= 1;
	printf("Enter the day of birth: ");
	scanf_s("%d", &person.birthday.tm_mday);
	printf("Enter the position: ");
	scanf_s("%s", &person.position, sizeof(person.position));
	printf("Enter the salary: ");
	scanf_s("%f", &person.salary);
	char clean_line[80];
	gets_s(clean_line, sizeof(clean_line));

	__time32_t curtime;
	_time32(&curtime);
	struct tm curtm;
	_localtime32_s(&curtm, &curtime);
	SetStartDay(&person, curtm.tm_year + 1900, curtm.tm_mon + 1, curtm.tm_mday);
	hrd->totalpersons++;
	hrd->persons = (Emploeye*)realloc(hrd->persons, hrd->totalpersons * sizeof(Emploeye));

	hrd->persons[hrd->totalpersons - 1] = person;

	return hrd->persons + hrd->totalpersons - 1;
}


Emploeye* AddNewEmploeyeFull(HumanResourcesDepartment* hrd) {
	Emploeye* pperson = AddNewEmploeyeShort(hrd);
	Emploeye& person = *pperson;
	printf("Enter the education: ");
	gets_s(person.education, sizeof(person.education) - 1);
	printf("Enter the pasport data: ");
	scanf_s("%s", &person.pasportdata, sizeof(person.pasportdata));
	printf("Enter the social protection card: ");
	scanf_s("%s", &person.socprotectcard, sizeof(person.socprotectcard));
	printf("Enter the coments: ");
	gets_s(person.coments, sizeof(person.coments) - 1);
	char clean_line[80];
	gets_s(clean_line, sizeof(clean_line));
	return pperson;
}

Emploeye* ChangeDataAboutEmploeye(Emploeye* person) {
	printf("What do you wanna change?: [S]urname, [N]ame, [F]athersname, [B]irthday, [P]assport, soc[C]ard, [E]ducation, p[O]sition, salar[Y], first [D]ay, co[M]ents :");
	switch (GetUserMenuInputChar()) {
	case 's':
	case 'S': {
		printf("Enter the surname: ");
		scanf_s("%s", person->surname, sizeof(person->surname));
		break;
	}
	case 'n':
	case 'N': {
		printf("Enter the name: ");
		scanf_s("%s", &person->name, sizeof(person->name));
		break;
	}
	case 'f':
	case 'F': {
		printf("Enter the fathersname: ");
		scanf_s("%s", &person->fathersname, sizeof(person->fathersname));
		break;
	}

	case 'b':
	case 'B': {
		printf("Enter the birthday:\n");
		printf("Enter the year of birth:");
		scanf_s("%d", &person->birthday.tm_year - 1900);
		printf("Enter the month of birth: ");
		scanf_s("%d", &person->birthday.tm_mon - 1);
		printf("Enter the day of birth: ");
		scanf_s("%d", &person->birthday.tm_mday);
		break;
	}
	case 'p':
	case 'P': {
		printf("Enter the pasport: ");
		scanf_s("%s", &person->pasportdata, sizeof(person->pasportdata));
		break;
	}
	case 'c':
	case 'C': {
		printf("Enter the position: ");
		scanf_s("%s", &person->socprotectcard, sizeof(person->socprotectcard));
		break;
	}
	case 'e':
	case 'E': {
		printf("Enter the education: ");
		scanf_s("%s", &person->education, sizeof(person->education));
		break;
	}
	case 'o':
	case 'O': {
		printf("Enter the position: ");
		scanf_s("%s", &person->position, sizeof(person->position));
		break;
	}
	case 'y':
	case 'Y': {
		printf("Enter the position: ");
		scanf_s("%f", &person->salary, sizeof(person->salary));
		break;
	}
	case 'd':
	case 'D': {
		printf("Enter the first work day data:\n");
		printf("Enter the year: ");
		scanf_s("%d", &person->startday.tm_year - 1900);
		printf("Enter the month: ");
		scanf_s("%d", &person->startday.tm_mon - 1);
		printf("Enter the day: ");
		scanf_s("%d", &person->startday.tm_mday);
		break;
	}
	case 'm':
	case 'M': {
		printf("Enter the coment: ");
		scanf_s("%s", &person->coments, sizeof(person->coments));
		break;
	}
	}
	return person;
}

void FireEmploeye(HumanResourcesDepartment* hrd, const int number) {
	if (number<0 || number>hrd->totalpersons) {
		printf("Invalid number! Reenter the value.");
		return;
	}
	size_t blocksize = (hrd->totalpersons - number) * sizeof(Emploeye);
	memmove_s(&hrd->persons[number - 1], blocksize, &hrd->persons[number], blocksize);
	hrd->totalpersons--;
}

int SortEmploeyesByFIO(const void* arg1, const void* arg2) {
	Emploeye* emploeye1 = (Emploeye*)arg1;
	Emploeye* emploeye2 = (Emploeye*)arg2;
	int cmp = strcmp(emploeye1->surname, emploeye2->surname);
	if (cmp) return cmp;
	cmp = strcmp(emploeye1->name, emploeye2->name);
	if (cmp) return cmp;
	return strcmp(emploeye1->fathersname, emploeye2->fathersname);
}

int SortEmploeyesByBirthday(const void* arg1, const void* arg2) {
	Emploeye* emploeye1 = (Emploeye*)arg1;
	Emploeye* emploeye2 = (Emploeye*)arg2;
	int cmp = emploeye1->birthday.tm_year - emploeye2->birthday.tm_year;
	if (cmp) return cmp;
	cmp = emploeye1->birthday.tm_mon - emploeye2->birthday.tm_mon;
	if (cmp) return cmp;
	return emploeye1->birthday.tm_mday - emploeye2->birthday.tm_mday;
}

int SortEmploeyesByFirstDayWork(const void* arg1, const void* arg2) {
	Emploeye* emploeye1 = (Emploeye*)arg1;
	Emploeye* emploeye2 = (Emploeye*)arg2;
	int cmp = emploeye1->startday.tm_year - emploeye2->startday.tm_year;
	if (cmp) return cmp;
	cmp = emploeye1->startday.tm_mon - emploeye2->startday.tm_mon;
	if (cmp) return cmp;
	return emploeye1->startday.tm_mday - emploeye2->startday.tm_mday;
}


void SortEmploeyes(HumanResourcesDepartment* hrd) {
	printf("[0-default] FIO sort [1] Birthday sort, [2] First day at work\n");
	switch (GetUserMenuInput())
	{
	case 0: {
		qsort(hrd->persons, hrd->totalpersons, sizeof(Emploeye), SortEmploeyesByFIO);
		printf("Data base was sorted by FIO.\n");
	}
	case 1: {
		qsort(hrd->persons, hrd->totalpersons, sizeof(Emploeye), SortEmploeyesByBirthday);
		printf("Data base was sorted by Birthday.\n");

	}
	case 2: {
		qsort(hrd->persons, hrd->totalpersons, sizeof(Emploeye), SortEmploeyesByFirstDayWork);
		printf("Data base was sorted by First day at work.\n");
	}
	}
	PrintEmployesInfoShort(hrd);
}

void ShowBirthdayNotice(HumanResourcesDepartment* hrd) {
	__time32_t noticelim = CreateNoticeLimit(7);
	__time32_t curtime = time(0);
	struct tm curtm;
	_localtime32_s(&curtm, &curtime);
	int showheader = 0;
	for (int i = 0; i < hrd->totalpersons; i++) {
		struct tm persontm = hrd->persons[i].birthday;
		persontm.tm_year = curtm.tm_year;
		time_t personbirthday = mktime(&persontm);
		if (personbirthday > curtime&& personbirthday < noticelim) {
			if (!showheader) {
				showheader = 1;
				printf("Those workers will have birthday in a week:\n");
			}
			PrintEmployeInfoShort(hrd->persons + i);
		}
	}
}

void ShowPencionerNotice(HumanResourcesDepartment* hrd) {
	time_t noticelim = CreateNoticeLimit(31);
	int showheader = 0;
	for (int i = 0; i < hrd->totalpersons; i++) {
		struct tm persontm = hrd->persons[i].birthday;
		persontm.tm_year += 65;

		if (mktime(&persontm) < noticelim) {
			if (!showheader) {
				showheader = 1;
				printf("Those workers are pre-retirment & retirement ages:\n");
			}
			PrintEmployeInfoShort(hrd->persons + i);
		}
	}
}

void ShowVacationNotice(HumanResourcesDepartment* hrd) {
	time_t noticelim = CreateNoticeLimit(-183);
	int showheader = 0;
	for (int i = 0; i < hrd->totalpersons; i++) {
		struct tm persontm = hrd->persons[i].startday;

		if (mktime(&persontm) < noticelim) {
			if (!showheader) {
				showheader = 1;
				printf("Give those workers vacation:\n");
			}
			PrintEmployeInfoShort(hrd->persons + i);
		}
	}
}

void Menu(HumanResourcesDepartment* hrd) {
	while (true) {
		system("cls");
		if (!hrd) {
			printf("Unexpected error! hrd object is not initialized.");
			exit(EXIT_FAILURE);
		}
		printf("\nWelcome to our company's human resources department! Choose one of the options:\n");
		printf("[1] Show all emploeyes.\n");
		printf("[2] Add an emploeye.\n");
		printf("[3] Edit emploeye info.\n");
		printf("[4] Change sort order.\n");
		printf("[5] Fire an emploeye.\n");
		printf("[0] Save & exit.\n");

		switch (GetUserMenuInput()) {

		case 1: {
			system("cls");
			PrintEmployesInfoShort(hrd);
			printf("Which emploeye's full info you wanna see?(press any other key to return) ");
			int i = GetUserMenuInput();
			if (i<1 || i>hrd->totalpersons) {
				printf("Invalid person number! Please enter correctly.");
				printf("Press Enter to continue");
				getchar();
				break;
			}
			PrintEmploeyesFullInfo(&hrd->persons[i - 1]);
			printf("Press Enter to continue");
			getchar();
			break;
		}
		case 2: {
			system("cls");
			printf("[0-defualt] Short add , [1] Full add\n");

			switch (GetUserMenuInput()) {
			case 0: AddNewEmploeyeShort(hrd); break;
			case 1: AddNewEmploeyeFull(hrd); break;
			default: break;
			}
			printf("Press Enter to continue");
			getchar();
			break;
		}
		case 3: {
			system("cls");
			PrintEmployesInfoShort(hrd);
			printf("Which emploeye's info you wanna change?(press any other key to return) ");
			int i = GetUserMenuInput();
			if (i<1 || i>hrd->totalpersons) {
				printf("Invalid person number! Please enter correctly.");
				break;
			}
			PrintEmploeyesFullInfo(&hrd->persons[i - 1]);
			ChangeDataAboutEmploeye(&hrd->persons[i - 1]);
			printf("Press Enter to continue");
			getchar();
			break;

		}
		case 4: {
			system("cls");
			SortEmploeyes(hrd);
			printf("Press Enter to continue");
			getchar();
			break;
		}

		case 5: {
			system("cls");
			printf("Choose the emploeye you wanna fire: ");
			FireEmploeye(hrd, GetUserMenuInput());
			printf("Press Enter to continue");
			getchar();
			break;
		}
		case 0: {
			if (!SaveHRD(hrd, hrdfilename)) {
				printf("ERROR! Could not save HRD database to %s!", hrdfilename);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		default: { printf("Invalid input.");
			printf("Press Enter to continue");
			getchar();
			break;
		}

		}
	}
}

void main(void)
{
	system("cls");
	HumanResourcesDepartment* hrd = LoadHRD(hrdfilename);
	if (!hrd) {
		printf("ERROR! Could not load HRD database from %s!", hrdfilename);
		exit(EXIT_FAILURE);
	}
	printf("\n");
	ShowBirthdayNotice(hrd);
	printf("\n");
	ShowPencionerNotice(hrd);
	printf("\n");
	ShowVacationNotice(hrd);
	printf("\n");
	printf("Press Enter to continue");
	getchar();
	Menu(hrd);

	exit(EXIT_SUCCESS);
}
