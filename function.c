// ID CHECK
int checkID(char *id)
{
    char line[100];
    FILE *file = fopen("account.txt", "r");
    while (fgets(line, 100, file))
    {
        char *token = strtok(line, ",");
        if (strcmp(token, id) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// SESSION CHECK
int checkSession(char *id)
{
    char line[100];
    FILE *file = fopen("session.txt", "r");
    while (fgets(line, 100, file))
    {
        char *token = strtok(line, ",");
        if (strcmp(token, id) == 0)
        {
            fclose(file);
            return 1;
        }
    }
}

// PASSWORD MASKING
void maskPassword(char *password)
{
    int i = 0;
    char c;

    while ((c = getch()) != '\r' && c != '\n')
    {
        if (c == 8 && i > 0) //8 = backspace
        {
            printf("\b \b");
            i--;
        }
        else if (c != 8)
        {
            printf("*");
            password[i] = c;
            i++;
        }
    }
    password[i] = '\0';
}

// ADMIN
void AddNewTutor()
{
    struct AdminMenu AM;
    printf("1. Add New Tutor\n");

    // ID CHECK
    int TutorExists = 0;
    do
    {
        printf("Please enter the tutor's ID: ");
        scanf("%s", AM.tutorID);

        TutorExists = checkID(AM.tutorID);
        if (TutorExists)
        {
            printf("ID already exists, please enter a different ID.\n");
        }
    } while (TutorExists);

    printf("Please enter the tutor's Name: ");
    scanf("%s", AM.tutorName);

    FILE *file = fopen("account.txt", "a");
    fprintf(file, "%s,123,tutor,%s,-blank\n", AM.tutorID, AM.tutorName);
    fclose(file);

    printf("\nTutor %s is added!\n\n", AM.tutorName);
}

void AddNewSession()
{
    struct Session ses;
    struct AdminMenu AM;
    while (1)
    {
        printf("2. Add a New Programming Cafe Session\n");

        int sesExist = 0;
        do
        {
            printf("Please enter the session's ID: ");
            scanf("%s", ses.sesID);

            sesExist = checkSession(ses.sesID);
            if (sesExist)
            {
                printf("ID already exists, please enter a different ID.\n");
            }
        } while (sesExist);

        // ADDING THE SESSION
        printf("PLease enter the session's code: ");
        scanf("%s", ses.sesCode);
        printf("PLease enter the session's name: ");
        scanf("%s", ses.sesTitle);
        printf("PLease enter the session's date: ");
        scanf("%s", ses.sesDay);
        printf("PLease enter the session's time: ");
        scanf("%s", ses.sesTime);
        printf("PLease enter the session's location: ");
        scanf("%s", ses.sesLocation);

        // MAKING SURE
        printf("\nSession ID: %s\n", ses.sesID);
        printf("Session Code: %s\n", ses.sesCode);
        printf("Session Name: %s\n", ses.sesTitle);
        printf("Session Date: %s\n", ses.sesDay);
        printf("Session Time: %s\n", ses.sesTime);
        printf("Session Location: %s\n", ses.sesLocation);
        printf("Is this session's detail correct(Y/N)? ");
        scanf("%s", AM.checkSes);

        while (strcmp(AM.checkSes, "Y") != 0 && strcmp(AM.checkSes, "N") != 0)
        {
            printf("Invalid input. Please enter Y or N: ");
            scanf("%s", AM.checkSes);
        }

        if (strcmp(AM.checkSes, "Y") == 0)
        {
            FILE *file = fopen("session.txt", "a");
            fprintf(file, "%s,%s,%s,%s,%s,%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation);
            fclose(file);

            printf("The session, %s is inputed\n", ses.sesTitle);
            break;
        }

        else if (strcmp(AM.checkSes, "N") == 0)
        {
            break;
        }
    }
}

void RegisterStudent()
{
    struct AdminMenu AM;
    printf("3. Register a Student\n");

    int exists = 0;
    do
    {
        printf("Please enter the student's ID: ");
        scanf("%s", AM.studentID);

        exists = checkID(AM.studentID);
        if (exists)
        {
            printf("ID already exists, please enter a different ID.\n");
        }
    } while (exists);

    printf("Please enter the student's Name: ");
    scanf("%s", AM.studentName);

    FILE *file = fopen("account.txt", "a");
    fprintf(file, "%s,123,student,%s,-blank\n", AM.studentID, AM.studentName);
    fclose(file);

    printf("\nStudent %s is added!\n\n", AM.studentName);
}

void StudentEnroll()
{
    struct Account acc;
    struct Session ses;
    struct StudentMenu SM;
    printf("4. Enroll a Student to a Session\n");

    int studentFound = 0;
    char studentUserID[30];
    char studentSesAdd[30] = "#";

    FILE *accfileR = fopen("account.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    printf("List of available Students:\n");

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "student") == 0)
        {
            strcpy(acc.usertype, acc.usertypetxt);
            strcpy(acc.username, acc.usernametxt);
            strcpy(acc.cafeses, acc.cafesession);
            int sesNum = 0;
            strcpy(SM.accSes, acc.cafeses);
            char *token = strtok(SM.accSes, "-");
            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }
            printf("Student ID: %s\n", acc.usertxt);
            printf("Name: %s\n", acc.usernametxt);
            printf("-------------------------------\n");
        }
    }
    fclose(accfileR);
    printf("-------------------------------\n");

    printf("Please enter the Student's ID: ");
    scanf("%s", studentUserID);

    accfileR = fopen("account.txt", "r");
    char sessionsID[9999] = "#";
    char takenSes[9999] = "";

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "student") == 0 && strcmp(acc.usertxt, studentUserID) == 0)
        {
            strcat(takenSes, acc.cafesession);
        }
    }
    strcat(takenSes, "-");

    fclose(accfileR);

    accfileR = fopen("account.txt", "r");

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertxt, studentUserID) == 0 && strcmp(acc.usertypetxt, "student") == 0)
        {
            studentFound = 1;
            strcpy(acc.usertype, acc.usertypetxt);
            strcpy(acc.username, acc.usernametxt);
            strcpy(acc.cafeses, acc.cafesession);

            int sesNum = 0;

            strcpy(SM.accSes, acc.cafeses);
            char *token = strtok(SM.accSes, "-");
            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }

            printf("List of Available Session(s): \n");

            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }
            FILE *sessionfile = fopen("session.txt", "r");

            while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
            {
                char temp[30] = "-";
                strcat(temp, ses.sesID);
                strcat(temp, "-");
                if (strstr(takenSes, temp) != NULL)
                {
                    continue;
                }
                strcat(sessionsID, ses.sesID);
                strcat(sessionsID, "#");
                printf("\nSession ID: %s\n", ses.sesID);
                printf("Session Title: %s\n", ses.sesTitle);
            }
            fclose(sessionfile);

            printf("\nPlease enter the session ID: ");
            scanf("%s", studentSesAdd);

            char temp[30] = "#";
            strcat(temp, studentSesAdd);
            strcat(temp, "#");
            if (strstr(sessionsID, temp) != NULL)
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s-%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession, studentSesAdd);
                printf("Session added successfully.\n");
            }
            else
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
                printf("Session ID not found!\n");
            }
        }
        else
        {
            fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
        }
    }

    if (!studentFound)
    {
        printf("%s is not a student.\n\n", studentUserID);
    }

    fclose(accfileR);
    fclose(tempFile);

    remove("account.txt");
    rename("temp.txt", "account.txt");
}

void ParticipantList()
{
    struct Session ses[30];
    struct Account acc[30];
    int sesCount = 0;
    int accCount = 0;

    // Read session.txt file
    FILE *sessionFile = fopen("session.txt", "r");
    if (sessionFile == NULL)
    {
        printf("Failed to open session.txt file.\n");
        return;
    }

    while (fscanf(sessionFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  ses[sesCount].sesID, ses[sesCount].sesCode, ses[sesCount].sesTitle,
                  ses[sesCount].sesDay, ses[sesCount].sesTime, ses[sesCount].sesLocation) != EOF)
    {
        sesCount++;
    }
    fclose(sessionFile);

    // Read account.txt file
    FILE *accFile = fopen("account.txt", "r");
    if (accFile == NULL)
    {
        printf("Failed to open account.txt file.\n");
        return;
    }

    while (fscanf(accFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  acc[accCount].usertxt, acc[accCount].passtxt, acc[accCount].usertypetxt,
                  acc[accCount].usernametxt, acc[accCount].cafesession) != EOF)
    {
        accCount++;
    }
    fclose(accFile);

    for (int i = 0; i < sesCount; i++)
    {
        printf("\nSession Code: %s\n", ses[i].sesCode);
        printf("Location: %s\n", ses[i].sesLocation);

        printf("Participants:\n");

        for (int j = 0; j < accCount; j++)
        {
            char sessionIDs[300];
            strcpy(sessionIDs, acc[j].cafesession);

            char *sessionID = strtok(sessionIDs, "-");

            while (sessionID != NULL)
            {
                if (strcmp(sessionID, ses[i].sesID) == 0)
                {
                    if (strcmp(acc[j].usertypetxt, "tutor") == 0)
                    {
                        printf("Tutor: %s\n", acc[j].usernametxt);
                    }
                    else if (strcmp(acc[j].usertypetxt, "student") == 0)
                    {
                        printf("Student: %s\n", acc[j].usernametxt);
                    }
                }
                sessionID = strtok(NULL, "-");
            }
        }

        printf("\n");
    }
}

void EnrollTutor()
{
    printf("6. Enroll a tutor to a session\n");
    struct TutorMenu TM;
    struct Account acc;
    struct Session ses;
    int tutorFound = 0;

    char tutorUserID[30];
    char tutorSesAdd[30] = "#";

    FILE *accfileR = fopen("account.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    printf("List of available Tutors:\n");

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "tutor") == 0)
        {
            strcpy(acc.usertype, acc.usertypetxt);
            strcpy(acc.username, acc.usernametxt);
            strcpy(acc.cafeses, acc.cafesession);
            int sesNum = 0;
            strcpy(TM.accSes, acc.cafeses);
            char *token = strtok(TM.accSes, "-");
            while (token != NULL)
            {
                TM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }
            if (sesNum == 1)
            {
                printf("TutorID: %s\n", acc.usertxt);
                printf("Name: %s\n", acc.usernametxt);
                printf("-------------------------------\n");
            }
        }
    }

    fclose(accfileR);
    printf("-------------------------------\n");

    printf("Please enter the Tutor's ID: ");
    scanf("%s", tutorUserID);

    accfileR = fopen("account.txt", "r");

    char sessionsID[9999] = "#";
    char takenSes[9999] = "";

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "tutor") == 0)
        {
            strcat(takenSes, acc.cafesession);
        }
    }
    strcat(takenSes, "-");

    fclose(accfileR);

    accfileR = fopen("account.txt", "r");

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertxt, tutorUserID) == 0 && strcmp(acc.usertypetxt, "tutor") == 0)
        {
            tutorFound = 1;
            strcpy(acc.usertype, acc.usertypetxt);
            strcpy(acc.username, acc.usernametxt);
            strcpy(acc.cafeses, acc.cafesession);

            int sesNum = 0;

            strcpy(TM.accSes, acc.cafeses);
            char *token = strtok(TM.accSes, "-");
            while (token != NULL)
            {
                TM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }

            if (sesNum == 2)
            {
                printf("This tutor has already been assigned to a session.\n");
                fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
                continue;
            }
            else
            {
                printf("List of Available Session(s): \n");

                char *token = strtok(TM.accSes, "-");
                while (token != NULL)
                {
                    TM.accTok[sesNum++] = token;
                    token = strtok(NULL, "-");
                }
                FILE *sessionfile = fopen("session.txt", "r");

                while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
                {

                    char temp[30] = "-";
                    strcat(temp, ses.sesID);
                    strcat(temp, "-");
                    if (strstr(takenSes, temp) != NULL)
                    {
                        continue;
                    }

                    strcat(sessionsID, ses.sesID);
                    strcat(sessionsID, "#");
                    printf("\nSession ID: %s\n", ses.sesID);
                    printf("Session Title: %s\n", ses.sesTitle);
                }
                fclose(sessionfile);
            }
            printf("\nPlease enter the session ID: ");
            scanf("%s", tutorSesAdd);

            char temp[30] = "#";
            strcat(temp, tutorSesAdd);
            strcat(temp, "#");
            if (strstr(sessionsID, temp) != NULL)
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s-%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession, tutorSesAdd);
                printf("Session added successfully.\n");
            }
            else
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
                printf("Session ID not found!\n");
            }
        }
        else
        {
            fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
        }
    }

    if (!tutorFound)
    {
        printf("%s is not a tutor.\n\n", tutorUserID);
    }

    fclose(accfileR);
    fclose(tempFile);

    remove("account.txt");
    rename("temp.txt", "account.txt");
}

// TUTOR
void TutorViewSession(struct TutorMenu TM, struct Account acc, struct Session ses)
{
    printf("1. View Listing Session(s)\n");

    int sesNum = 0;

    strcpy(TM.accSes, acc.cafeses);
    char *token = strtok(TM.accSes, "-");
    while (token != NULL)
    {
        TM.accTok[sesNum++] = token;
        token = strtok(NULL, "-");
    }

    FILE *sessionfile = fopen("session.txt", "r");

    while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
    {
        for (int i = 0; i < sesNum; i++)
        {
            if (strcmp(ses.sesID, TM.accTok[i]) == 0)
            {
                printf("\nSession Title: %s\n", ses.sesTitle);
                printf("Session Day: %s\n", ses.sesDay);
                printf("Session Time: %s\n", ses.sesTime);
                printf("Session Location: %s\n", ses.sesLocation);
            }
        }
    }
    fclose(sessionfile);
}

// STUDENT
void StudentViewSession(struct Account acc, struct Session ses, struct StudentMenu SM)
{
    printf("1. View Listing Session(s):\n");

    FILE *accfile = fopen("account.txt", "r");

    while (fscanf(accfile, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "student") == 0 && strcmp(acc.username, acc.usernametxt) == 0)
        {

            int sesNum = 0;
            FILE *sessionfile = fopen("session.txt", "r");

            strcpy(SM.accSes, acc.cafesession);
            char *token = strtok(SM.accSes, "-");
            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }

            while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
            {
                for (int i = 0; i < sesNum; i++)
                {
                    if (strcmp(ses.sesID, SM.accTok[i]) == 0)
                    {
                        printf("\nSession Title: %s\n", ses.sesTitle);
                        printf("Session Day: %s\n", ses.sesDay);
                        printf("Session Time: %s\n", ses.sesTime);
                        printf("Session Location: %s\n", ses.sesLocation);
                    }
                }
            }
            fclose(sessionfile);
            fclose(accfile);
        }
    }
}

void studentEnroll(struct Account acc, struct Session ses, struct StudentMenu SM)
{
    printf("2. Enroll to a Session:\n");

    int studentFound = 0;

    char studentSesAdd[30] = "#";

    FILE *accfileR = fopen("account.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    char sessionsID[9999] = "#";
    char takenSes[9999] = "";

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usertypetxt, "student") == 0 && strcmp(acc.usernametxt, acc.username) == 0)
        {
            strcat(takenSes, acc.cafesession);
        }
    }
    strcat(takenSes, "-");

    fclose(accfileR);

    accfileR = fopen("account.txt", "r");

    while (fscanf(accfileR, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
    {
        if (strcmp(acc.usernametxt, acc.username) == 0 && strcmp(acc.usertypetxt, "student") == 0)
        {
            studentFound = 1;
            strcpy(acc.usertype, acc.usertypetxt);
            strcpy(acc.username, acc.usernametxt);
            strcpy(acc.cafeses, acc.cafesession);

            int sesNum = 0;

            strcpy(SM.accSes, acc.cafeses);
            char *token = strtok(SM.accSes, "-");
            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }

            printf("List of Available Session(s): \n");

            while (token != NULL)
            {
                SM.accTok[sesNum++] = token;
                token = strtok(NULL, "-");
            }
            FILE *sessionfile = fopen("session.txt", "r");

            while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
            {
                char temp[30] = "-";
                strcat(temp, ses.sesID);
                strcat(temp, "-");
                if (strstr(takenSes, temp) != NULL)
                {
                    continue;
                }
                strcat(sessionsID, ses.sesID);
                strcat(sessionsID, "#");
                printf("\nSession ID: %s\n", ses.sesID);
                printf("Session Title: %s\n", ses.sesTitle);
            }
            fclose(sessionfile);

            printf("\nPlease enter the session ID: ");
            scanf("%s", studentSesAdd);

            char temp[30] = "#";
            strcat(temp, studentSesAdd);
            strcat(temp, "#");
            if (strstr(sessionsID, temp) != NULL)
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s-%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession, studentSesAdd);
                printf("Session added successfully.\n");
            }
            else
            {
                fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
                printf("Session ID not found!\n");
            }
        }
        else
        {
            fprintf(tempFile, "%s,%s,%s,%s,%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession);
        }
    }

    fclose(accfileR);
    fclose(tempFile);

    remove("account.txt");
    rename("temp.txt", "account.txt");
}

// SEE TIME TABLE
void SeeTimeTable()
{
    struct Session ses;
    printf("See Timetable\n");
    printf("----------------------------------------------------------\n");
    FILE *sessionfile = fopen("session.txt", "r");

    while (fscanf(sessionfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ses.sesID, ses.sesCode, ses.sesTitle, ses.sesDay, ses.sesTime, ses.sesLocation) != EOF)
    {
        printf("\nSession Title: %s\n", ses.sesTitle);
        printf("Session Day: %s\n", ses.sesDay);
        printf("Session Time: %s\n", ses.sesTime);
        printf("Session Location: %s\n", ses.sesLocation);
    }
    fclose(sessionfile);
    printf("----------------------------------------------------------\n");
    printf("\n");
}