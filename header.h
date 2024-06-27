#ifndef HEADER_H
#define HEADER_H

// STRUCTS
struct Account
{
    char user[30], pass[30];
    char usertxt[30], passtxt[30], usertypetxt[30];
    char userID[30], username[30], usernametxt[30], usertype[30];
    char cafeses[300], cafesession[300];
};

struct Session
{
    char sesID[30], sesCode[30], sesTitle[300], sesDay[30], sesTime[30], sesLocation[30];
};

struct AdminMenu
{
    char adminMenu[10];
    char tutorID[10], tutorName[10];
    char studentID[10], studentName[10];
    char checkSes[30];
};

struct TutorMenu
{
    char tutorMenu[10];
    char accSes[100];
    char *accTok[10];
};

struct StudentMenu
{
    char studentMenu[10];
    char accSes[100];
    char *accTok[10];
};

// MAIN MENU
void maskPassword();
void SeeTimeTable();

// ADMIN FUNCTIONS
void AddNewTutor();
void AddNewSession();
void RegisterStudent();
void StudentEnroll();
void ParticipantList();
void EnrollTutor();

// TUTOR FUNCTION
void TutorViewSession(struct TutorMenu TM, struct Account acc, struct Session ses);

//STUDENT FUNCTION
void StudentViewSession(struct Account acc, struct Session ses, struct StudentMenu SM);
void studentEnroll(struct Account acc, struct Session ses, struct StudentMenu SM);

#endif