#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "header.h"
#include "function.c"

int main()
{
    while (1)
    {
        // MAIN MENU
        char mainMenu[10];
        printf("1. Login\n");
        printf("2. See Timetable\n");
        printf("3. Exit\n");
        printf("Select a menu: ");
        scanf("%s", mainMenu);
        printf("\n");

        // 1. LOGIN
        if (strcmp(mainMenu, "1") == 0)
        {
            struct Account acc;
            struct Session ses;
            int login = 0;

            FILE *accfile = fopen("account.txt", "r");

            printf("Please enter your username: ");
            scanf("%s", acc.user);
            printf("Please enter your password: ");
            maskPassword(acc.pass);

            while (fscanf(accfile, "%[^,],%[^,],%[^,],%[^,],%s\n", acc.usertxt, acc.passtxt, acc.usertypetxt, acc.usernametxt, acc.cafesession) != EOF)
            {
                if (strcmp(acc.user, acc.usertxt) == 0 && strcmp(acc.pass, acc.passtxt) == 0)
                {
                    login = 1;
                    strcpy(acc.usertype, acc.usertypetxt);
                    strcpy(acc.username, acc.usernametxt);
                    strcpy(acc.cafeses, acc.cafesession);
                }
            }

            fclose(accfile);

            // IF USERNAME AND PASS MATCH
            if (login == 1)
            {
                if (strcmp(acc.usertype, "admin") == 0)
                {
                    printf("\nWelcome Admin : %s", acc.username);
                    while (1)
                    {
                        // ADMIN MENU
                        struct AdminMenu AM;
                        printf("\n");
                        printf("1. Add a new tutor\n");
                        printf("2. Add a new programming cafe session\n");
                        printf("3. Register a student\n");
                        printf("4. Enroll a student to a session\n");
                        printf("5. List of programming cafe sessions and participating students\n");
                        printf("6. Enroll a tutor to a session\n");
                        printf("7. Logout\n");
                        printf("What do you want to do? ");
                        scanf("%s", AM.adminMenu);
                        printf("\n\n");

                        // ADD NEW TUTOR
                        if (strcmp(AM.adminMenu, "1") == 0)
                        {
                            AddNewTutor();
                        }

                        // ADD NEW PROGRAMMING CAFE SESSION
                        else if (strcmp(AM.adminMenu, "2") == 0)
                        {
                            AddNewSession();
                        }

                        // REGISTER A STUDENT
                        else if (strcmp(AM.adminMenu, "3") == 0)
                        {
                            RegisterStudent();
                        }

                        // ENROLL A STUDENT TO A SESSION
                        else if (strcmp(AM.adminMenu, "4") == 0)
                        {
                            StudentEnroll();
                        }

                        // LIST OF PROGRAMMING CAFE SESSIONS AND PARTICIPATING STUDENTS
                        else if (strcmp(AM.adminMenu, "5") == 0)
                        {
                            ParticipantList();
                        }

                        // ENROLL A TUTOR TO A SESSION
                        else if (strcmp(AM.adminMenu, "6") == 0)
                        {
                            EnrollTutor();
                        }

                        // LOGOUT
                        else if (strcmp(AM.adminMenu, "7") == 0)
                        {
                            break;
                        }

                        // ELSE
                        else
                        {
                            printf("Invalid Input!\n");
                        }
                    }
                }

                // TUTOR
                else if (strcmp(acc.usertype, "tutor") == 0)
                {
                    printf("\nWelcome tutor: %s\n", acc.username);
                    while (1)
                    {
                        struct TutorMenu TM;
                        printf("\n");
                        printf("1. View Listing Session(s)\n");
                        printf("2. Logout\n");
                        printf("What do you want to do? ");
                        scanf("%s", TM.tutorMenu);
                        printf("\n");

                        //View Listing Session
                        if (strcmp(TM.tutorMenu, "1") == 0)
                        {
                            TutorViewSession(TM, acc, ses);
                        }

                        //Logout
                        else if (strcmp(TM.tutorMenu, "2") == 0)
                        {
                            break;
                        }

                        //Invalid Input
                        else
                        {
                            printf("Invalid Input!\n");
                        }
                    }
                }

                // STUDENT
                else if (strcmp(acc.usertype, "student") == 0)
                {
                    printf("\nWelcome student: %s\n", acc.username);
                    while (1)
                    {
                        struct StudentMenu SM;
                        printf("\n");
                        printf("1. View Listing Session(s)\n");
                        printf("2. Enroll to a Session(s)\n");
                        printf("3. Logout\n");
                        printf("What do you want to do? ");
                        scanf("%s", SM.studentMenu);
                        printf("\n");

                        // VIEW LISTING SESSIONS
                        if (strcmp(SM.studentMenu, "1") == 0)
                        {
                            StudentViewSession(acc, ses, SM);
                        }

                        // ENROLL SESSION
                        else if (strcmp(SM.studentMenu, "2") == 0)
                        {
                            studentEnroll(acc, ses, SM);
                        }

                        // LOGOUT
                        else if (strcmp(SM.studentMenu, "3") == 0)
                        {
                            break;
                        }

                        // ELSE
                        else
                        {
                            printf("Invalid Input\n");
                        }
                    }
                }

                // ELSE
                else
                {
                    printf("User type not found!");
                }
            }

            // IF USERNAME AND PASS DOES NOT MATCH
            else
            {
                printf("\nWrong username or password!\n\n");
            }

            fclose(accfile);
        }

        // 2. SEE TIME TABLE
        else if (strcmp(mainMenu, "2") == 0)
        {
            SeeTimeTable();
        }

        // 3. EXIT
        else if (strcmp(mainMenu, "3") == 0)
        {
            break;
        }

        // ELSE
        else
        {
            printf("Invalid Input\n\n");
        }
    }

    return 0;
}