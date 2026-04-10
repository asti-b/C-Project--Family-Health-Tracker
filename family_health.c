/*
  Family Health Tracker -
      * anxiety test
      * depression test
      * BMI calculation
      * Blood pressure / heart rate inputs
      * Sleep tracking: hours & cycles, detailed evaluation (age+cycles)
      * Save to text file, export CSV
      * Add / Update / Delete / Search members
      * Lots of comments and explanations
  - Compile with: gcc family_health_long.c -o family_health
  - Run: ./family_health
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEXT_FILE "health_records_verbose.txt"
#define CSV_FILE  "health_records_verbose.csv"

#define MAX_NAME 120
#define MAX_MED 256
#define MAX_ALLERGY 256
#define MAX_CONTACT 32

typedef struct {
    char name[MAX_NAME];
    int age;

    float weight;
    float height;
    float bmi;

    float bp_sys;
float bp_dia;
    float heartrate;

    float fastingsugar;
    float postmealsugar;
    float cholesterol;

    int gad7[7];
    int anxietyscore;
    char anxietycategory[32];

    int phq9[9];
    int depressionscore;
    char depressioncategory[32];

    float sleephours;
    int sleepcycles;
    char sleepquality[48];
    char sleepexplanation[256];

    char medications[MAX_MED];
    char allergies[MAX_ALLERGY];
    char emergencycontact[MAX_CONTACT];

} health;

void readlinesafe(const char *instring, char *outstring, size_t sz, char *b) {
    if (instring && strlen(instring) > 0) {
        printf("%s", instring);
    }
    if (!fgets(b, (int)sz, stdin)) {
        outstring[0] = '\0';
        return;
    }
    size_t len = strlen(b);
    if (len > 0 && b[len - 1] == '\n') b[len - 1] = '\0';
    strncpy(outstring, b, sz - 1);
    outstring[sz - 1] = '\0';
}

int readintsafe(const char *instring, char *b) {
    int val;
    while (1) {
        if (instring && strlen(instring) > 0) printf("%s", instring);
        if (!fgets(b, 128, stdin)) return 0;
        if (sscanf(b, "%d", &val) == 1) return val;
        printf("  -> Invalid input. Please enter an integer.\n");
    }
}

float readfloatsafe(const char *instring, char *b) {
    float val;
    while (1) {
        if (instring && strlen(instring) > 0) printf("%s", instring);
        if (!fgets(b, 128, stdin)) return 0.0f;
        if (sscanf(b, "%f", &val) == 1) return val;
        printf("  -> Invalid input. Please enter a number.\n");
    }
}

void tolowertrim(const char *src, char *outstring, size_t sz) {
    size_t i = 0, j = 0;
    while (src[i] != '\0' && j + 1 < sz) {
        char c = src[i++];
        if (!isspace((unsigned char)c)) {
            outstring[j++] = (char)tolower((unsigned char)c);
        }
    }
    outstring[j] = '\0';
}

void calculatebmi(health *rec) {
    if (rec->height > 0.0001f) {
        rec->bmi = rec->weight / (rec->height * rec->height);
    } else {
        rec->bmi = 0.0f;
    }
}

const char* getbmicategory(float bmi) {
    if (bmi <= 0.0f) return "Unknown";
    if (bmi < 18.5f) return "Underweight";
    if (bmi < 25.0f) return "Normal";
    if (bmi < 30.0f) return "Overweight";
    return "Obese";
}

const char* getbpcategory(float sys, float dia) {
    if (sys <= 0.0f || dia <= 0.0f) return "Unknown";
    if (sys < 120.0f && dia < 80.0f) return "Normal";
    if (sys < 130.0f && dia < 80.0f) return "Elevated";
    if (sys < 140.0f || dia < 90.0f) return "Stage 1 Hypertension";
    return "Stage 2 Hypertension";
}

const char* getsugarcategory(float f, float p) {
    if (f <= 0.0f && p <= 0.0f) return "Unknown";
    if (f < 100.0f && p < 140.0f) return "Normal";
    if (f <= 125.0f || p <= 199.0f) return "Pre-diabetic";
    return "Diabetic";
}

const char* getcholcategory(float c) {
    if (c <= 0.0f) return "Unknown";
    if (c < 200.0f) return "Desirable";
    if (c < 240.0f) return "Borderline High";
    return "High";
}

void setanxietycategory(health *rec) {
    int s = rec->anxietyscore;
    if (s == 0 && rec->gad7[0] == 0 && rec->gad7[1] == 0 && rec->gad7[2] == 0 &&
        rec->gad7[3] == 0 && rec->gad7[4] == 0 && rec->gad7[5] == 0 && rec->gad7[6] == 0) {
        strcpy(rec->anxietycategory, "Not taken");
        return;
    }
    if (s <= 4) strcpy(rec->anxietycategory, "Minimal");
    else if (s <= 9) strcpy(rec->anxietycategory, "Mild");
    else if (s <= 14) strcpy(rec->anxietycategory, "Moderate");
    else strcpy(rec->anxietycategory, "Severe");
}

void setdepressioncategory(health *rec) {
    int s = rec->depressionscore;
    if (s == 0 && rec->phq9[0] == 0 && rec->phq9[1] == 0 && rec->phq9[2] == 0 &&
        rec->phq9[3] == 0 && rec->phq9[4] == 0 && rec->phq9[5] == 0 && rec->phq9[6] == 0 &&
        rec->phq9[7] == 0 && rec->phq9[8] == 0) {
        strcpy(rec->depressioncategory, "Not taken");
        return;
    }
    if (s <= 4) strcpy(rec->depressioncategory, "Minimal");
    else if (s <= 9) strcpy(rec->depressioncategory, "Mild");
    else if (s <= 14) strcpy(rec->depressioncategory, "Moderate");
    else if (s <= 19) strcpy(rec->depressioncategory, "Moderately Severe");
    else strcpy(rec->depressioncategory, "Severe");
}
int askonescaledquestion(const char *question, char *b, int *p) {
    printf("\n%s\n", question);
    printf("  0 = Not at all\n  1 = Several days\n  2 = More than half the days\n  3 = Nearly every day\n");
    while (1) {
        printf("Answer (0-3): ");
        if (!fgets(b, 128, stdin)) return 0;
        if (sscanf(b, "%d", p) == 1) {
            if (*p >= 0 && *p <= 3) return *p;
            printf("  -> Please enter 0, 1, 2, or 3\n");
        } else {
            printf("  -> Invalid input. Please enter 0,1,2 or 3.\n");
        }
    }
}

void rungad7(health *rec, char *b, int *p) {
    const char *gadq[7] = {
        "1) Feeling nervous, anxious, or on edge",
        "2) Not being able to stop or control worrying",
        "3) Worrying too much about different things",
        "4) Trouble relaxing",
        "5) Being so restless that it is hard to sit still",
        "6) Becoming easily annoyed or irritable",
        "7) Feeling afraid as if something awful might happen"
    };
    int sum = 0;

    printf("\n--- GAD-7 (Anxiety) Test for %s ---\n", rec->name);
    for (int i = 0; i < 7; ++i) {
        int ans = askonescaledquestion(gadq[i], b, p);
        rec->gad7[i] = ans;
        sum += ans;
    }
    rec->anxietyscore = sum;
    setanxietycategory(rec);
    printf("\nGAD-7 completed. Score = %d (%s)\n", rec->anxietyscore, rec->anxietycategory);
}

void runphq9(health *rec, char *b, int *p) {
    const char *phqq[9] = {
"1) Little interest or pleasure in doing things",
        "2) Feeling down, depressed, or hopeless",
        "3) Trouble falling or staying asleep, or sleeping too much",
        "4) Feeling tired or having little energy",
        "5) Poor appetite or overeating",
        "6) Feeling bad about yourself — or that you are a failure",
        "7) Trouble concentrating on things",
        "8) Moving or speaking slowly OR being restless",
        "9) Thoughts that you would be better off dead or of hurting yourself"
    };
    int sum = 0;
    printf("\n--- PHQ-9 (Depression) Test for %s ---\n", rec->name);
    for (int i = 0; i < 9; ++i) {
        int ans = askonescaledquestion(phqq[i], b, p);
        rec->phq9[i] = ans;
        sum += ans;
    }
    rec->depressionscore = sum;
    setdepressioncategory(rec);
    printf("\nPHQ-9 completed. Score = %d (%s)\n", rec->depressionscore, rec->depressioncategory);
}

void recommendedsleephoursforage(int age, float *minh, float *maxh) {
    if (age <= 1) { *minh = 11.0f; *maxh = 14.0f; }
    else if (age <= 5) { *minh = 10.0f; *maxh = 13.0f; }
    else if (age <= 13) { *minh = 9.0f; *maxh = 11.0f; }
    else if (age <= 17) { *minh = 8.0f; *maxh = 10.0f; }
    else if (age <= 64) { *minh = 7.0f; *maxh = 9.0f; }
    else { *minh = 7.0f; *maxh = 8.0f; }
}

void evaluatesleepcombined(health *rec) {
    float minh, maxh;
    recommendedsleephoursforage(rec->age, &minh, &maxh);

    rec->sleepquality[0] = '\0';
    rec->sleepexplanation[0] = '\0';

    const char *hourcategory;
    if (rec->sleephours < minh) hourcategory = "Insufficient";
    else if (rec->sleephours <= maxh) hourcategory = "Healthy";
    else hourcategory = "Excessive";

    const char *cyclecategory;
    if (rec->sleepcycles < 4) cyclecategory = "Low cycles";
    else if (rec->sleepcycles <= 6) cyclecategory = "Healthy cycles";
    else cyclecategory = "High cycles (possible fragmented sleep)";

    snprintf(rec->sleepquality, sizeof(rec->sleepquality),
             "%s (%s)", hourcategory, cyclecategory);

    snprintf(rec->sleepexplanation, sizeof(rec->sleepexplanation),
             "Age: %d years. Recommended sleep for age: %.1f - %.1f hours/night.\n"
             "Recorded: %.2f hours/night, %d cycles.\n"
             "Hours evaluation: %s. Cycle evaluation: %s.\n",
             rec->age, minh, maxh, rec->sleephours, rec->sleepcycles,
             hourcategory, cyclecategory);

    if (strcmp(hourcategory, "Healthy") == 0 && strcmp(cyclecategory, "Healthy cycles") == 0) {
        strncat(rec->sleepexplanation, "Overall: Sleep appears adequate for age and cycles are healthy.\n",
                sizeof(rec->sleepexplanation) - strlen(rec->sleepexplanation) - 1);
    } else {
        if (strcmp(hourcategory, "Insufficient") == 0) {
            strncat(rec->sleepexplanation, "Advice: Consider increasing sleep duration. Try consistent bedtime, reduce screens before bed.\n",
                    sizeof(rec->sleepexplanation) - strlen(rec->sleepexplanation) - 1);
        } else if (strcmp(hourcategory, "Excessive") == 0) {
            strncat(rec->sleepexplanation, "Advice: If oversleeping regularly, consider assessing for sleep disorders or depression; consult physician if worried.\n",
                    sizeof(rec->sleepexplanation) - strlen(rec->sleepexplanation) - 1);
        }
        if (strcmp(cyclecategory, "Low cycles") == 0) {
            strncat(rec->sleepexplanation, "Low cycles may indicate too-short sleep or difficulties achieving REM. Aim for longer continuous sleep blocks.\n",
                    sizeof(rec->sleepexplanation) - strlen(rec->sleepexplanation) - 1);
        } else if (strcmp(cyclecategory, "High cycles (possible fragmented sleep)") == 0) {
            strncat(rec->sleepexplanation, "High cycles may indicate fragmented sleep — consider sleep hygiene, manage noise/light, or see specialist if persistent.\n",
                    sizeof(rec->sleepexplanation) - strlen(rec->sleepexplanation) - 1);
        }
    }
}
void savealltotext(health *h, int n) {
    FILE *fp = fopen(TEXT_FILE, "w");
    if (!fp) {
        printf("Error: cannot open %s for write.\n", TEXT_FILE);
        return;
    }
    fprintf(fp, "Family Health Records \n");
    for (int i = 0; i < n; ++i) {
        health *r = &h[i];
        fprintf(fp, "\tMember %d =\n", i+1);
        fprintf(fp, "Name: %s\n", r->name);
        fprintf(fp, "Age: %d\n", r->age);
        fprintf(fp, "Weight: %.2f kg\n", r->weight);
        fprintf(fp, "Height: %.2f m\n", r->height);
        fprintf(fp, "BMI: %.2f (%s)\n", r->bmi, getbmicategory(r->bmi));
        fprintf(fp, "BP: %.2f / %.2f (%s)\n", r->bp_sys, r->bp_dia, getbpcategory(r->bp_sys, r->bp_dia));
        fprintf(fp, "Heart rate: %.2f bpm\n", r->heartrate);
        fprintf(fp, "Fasting sugar: %.2f mg/dL\n", r->fastingsugar);
        fprintf(fp, "Post meal sugar: %.2f mg/dL\n", r->postmealsugar);
        fprintf(fp, "Cholesterol: %.2f mg/dL (%s)\n", r->cholesterol, getcholcategory(r->cholesterol));
        fprintf(fp, "Anxiety (GAD-7) score: %d (%s)\n", r->anxietyscore, r->anxietycategory);
        fprintf(fp, "Depression (PHQ-9) score: %d (%s)\n", r->depressionscore, r->depressioncategory);
        fprintf(fp, "Sleep: %.2f hours, %d cycles -> %s\n", r->sleephours, r->sleepcycles, r->sleepquality);
        fprintf(fp, "Sleep explanation: %s\n", r->sleepexplanation);
        fprintf(fp, "Medications: %s\n", r->medications);
        fprintf(fp, "Allergies: %s\n", r->allergies);
        fprintf(fp, "Emergency contact: %s\n", r->emergencycontact);
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("✔ Saved detailed records to %s\n", TEXT_FILE);
}
void exportalltocsv(health *h, int n) {
    FILE *fp = fopen(CSV_FILE, "w");
    if (!fp) {
        printf("Error: cannot open %s for export.\n", CSV_FILE);
        return;
    }
    fprintf(fp,
        "Name,Age,Weight,Height,BMI,BMI_Category,BP_Sys,BP_Dia,BP_Category,HeartRate,"
        "FastingSugar,PostMealSugar,SugarCategory,Cholesterol,CholCategory,"
        "GAD7_Score,GAD7_Category,PHQ9_Score,PHQ9_Category,SleepHours,SleepCycles,SleepQuality,Medications,Allergies,EmergencyContact\n"
    );

    for (int i = 0; i < n; ++i) {
        health *r = &h[i];
        fprintf(fp,
            "\"%s\",%d,%.2f,%.2f,%.2f,\"%s\",%.2f,%.2f,\"%s\",%.2f,%.2f,%.2f,\"%s\",%.2f,\"%s\",%d,\"%s\",%d,\"%s\",%.2f,%d,\"%s\",\"%s\",\"%s\",\"%s\"\n",
            r->name, r->age, r->weight, r->height, r->bmi, getbmicategory(r->bmi),
            r->bp_sys, r->bp_dia, getbpcategory(r->bp_sys, r->bp_dia), r->heartrate,
            r->fastingsugar, r->postmealsugar, getsugarcategory(r->fastingsugar, r->postmealsugar),
            r->cholesterol, getcholcategory(r->cholesterol),
            r->anxietyscore, r->anxietycategory, r->depressionscore, r->depressioncategory,
            r->sleephours, r->sleepcycles, r->sleepquality, r->medications, r->allergies, r->emergencycontact
        );
    }
    fclose(fp);
    printf("✔ Exported records to CSV file %s\n", CSV_FILE);
}
/* --------------------------- CRUD: Add / Update / Delete / Search --------------------------- */

health* addmember(health *h, int *n, char *b, int *p) {
    health newrec;
    memset(&newrec, 0, sizeof(health));

    readlinesafe("Enter name: ", newrec.name, sizeof(newrec.name), b);
    newrec.age = readintsafe("Enter age (years): ", b);
    newrec.weight = readfloatsafe("Enter weight (kg): ", b);
    newrec.height = readfloatsafe("Enter height (m): ", b);
    newrec.bp_sys = readfloatsafe("Enter systolic BP (mmHg): ", b);
    newrec.bp_dia = readfloatsafe("Enter diastolic BP (mmHg): ", b);
    newrec.heartrate = readfloatsafe("Enter heart rate (bpm): ", b);
    newrec.fastingsugar = readfloatsafe("Enter fasting blood sugar (mg/dL): ", b);
    newrec.postmealsugar = readfloatsafe("Enter post-meal blood sugar (mg/dL): ", b);
    newrec.cholesterol = readfloatsafe("Enter total cholesterol (mg/dL): ", b);

    for (int i = 0; i < 7; ++i) newrec.gad7[i] = 0;
    newrec.anxietyscore = 0;
    strcpy(newrec.anxietycategory, "Not taken");
    for (int i = 0; i < 9; ++i) newrec.phq9[i] = 0;
    newrec.depressionscore = 0;
    strcpy(newrec.depressioncategory, "Not taken");

    int takechoice = readintsafe("Take tests now? (1=Anxiety, 2=Depression, 3=Both, 0=None): ", b);
    if (takechoice == 1) rungad7(&newrec, b, p);
    else if (takechoice == 2) runphq9(&newrec, b, p);
    else if (takechoice == 3) { rungad7(&newrec, b, p); runphq9(&newrec, b, p); }

    newrec.sleephours = readfloatsafe("Enter average sleep hours per night: ", b);
    newrec.sleepcycles = readintsafe("Enter approx number of sleep cycles (integer): ", b);
    evaluatesleepcombined(&newrec);

    readlinesafe("Medications (comma separated, or 'None'): ", newrec.medications, sizeof(newrec.medications), b);
    readlinesafe("Allergies (comma separated, or 'None'): ", newrec.allergies, sizeof(newrec.allergies), b);
    readlinesafe("Emergency contact (phone/name): ", newrec.emergencycontact, sizeof(newrec.emergencycontact), b);
        health *tmp = realloc(h, (*n + 1) * sizeof(health));
    if (!tmp) {
        printf("Error: memory allocation failed while adding member.\n");
        return h;
    }
    h = tmp;
    h[*n] = newrec;
    (*n)++;
    printf("✔ Added member '%s' (total members: %d)\n", newrec.name, *n);
    return h;
}

void updatemember(health *h, int idx, char *b, int *p) {
    if (!h) return;
    if (idx < 0) return;
    health *rec = &h[idx];
    printf("\n--- Update member: %s ---\n", rec->name);
    printf("Press ENTER to keep current value shown in [brackets].\n");

    printf("Current name: [%s]\n", rec->name);
    readlinesafe("New name (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) strncpy(rec->name, b, sizeof(rec->name)-1);

    printf("Current age: [%d]\n", rec->age);
    readlinesafe("New age (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) {
        int val;
        if (sscanf(b, "%d", &val) == 1) rec->age = val;
    }

    printf("Current weight (kg): [%.2f]\n", rec->weight);
    readlinesafe("New weight (kg) (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) {
        float fv;
        if (sscanf(b, "%f", &fv) == 1) rec->weight = fv;
    }

    printf("Current height (m): [%.2f]\n", rec->height);
    readlinesafe("New height (m) (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) {
        float fv;
        if (sscanf(b, "%f", &fv) == 1) rec->height = fv;
    }

    printf("Current systolic BP: [%.2f]\n", rec->bp_sys);
    readlinesafe("New systolic BP (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->bp_sys = fv; }

    printf("Current diastolic BP: [%.2f]\n", rec->bp_dia);
    readlinesafe("New diastolic BP (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->bp_dia = fv; }

    printf("Current heart rate (bpm): [%.2f]\n", rec->heartrate);
    readlinesafe("New heart rate (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->heartrate = fv; }

    printf("Current fasting sugar: [%.2f]\n", rec->fastingsugar);
    readlinesafe("New fasting sugar (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->fastingsugar = fv; }

    printf("Current post-meal sugar: [%.2f]\n", rec->postmealsugar);
    readlinesafe("New post-meal sugar (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->postmealsugar = fv; }

    printf("Current cholesterol: [%.2f]\n", rec->cholesterol);
    readlinesafe("New cholesterol (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->cholesterol = fv; }
    printf("Retake tests? (1=Anxiety, 2=Depression, 3=Both, 0=None): ");
    int choice;
    if (!fgets(b, 128, stdin)) return;
    if (sscanf(b, "%d", &choice) == 1) {
        if (choice == 1) rungad7(rec, b, p);
        else if (choice == 2) runphq9(rec, b, p);
        else if (choice == 3) { rungad7(rec, b, p); runphq9(rec, b, p); }
    }

    printf("Current sleep hours: [%.2f], cycles: [%d]\n", rec->sleephours, rec->sleepcycles);
    readlinesafe("New sleep hours (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { float fv; if (sscanf(b, "%f", &fv) == 1) rec->sleephours = fv; }

    readlinesafe("New sleep cycles (or Enter to keep): ", b, 128, b);
    if (strlen(b) > 0) { int iv; if (sscanf(b, "%d", &iv) == 1) rec->sleepcycles = iv; }

    evaluatesleepcombined(rec);

    printf("Current medications: [%s]\n", rec->medications);
    readlinesafe("New medications (or Enter to keep): ", b, sizeof(rec->medications), b);
    if (strlen(b) > 0) strncpy(rec->medications, b, sizeof(rec->medications)-1);

    printf("Current allergies: [%s]\n", rec->allergies);
    readlinesafe("New allergies (or Enter to keep): ", b, sizeof(rec->allergies), b);
    if (strlen(b) > 0) strncpy(rec->allergies, b, sizeof(rec->allergies)-1);

    printf("Current emergency contact: [%s]\n", rec->emergencycontact);
    readlinesafe("New emergency contact (or Enter to keep): ", b, sizeof(rec->emergencycontact), b);
    if (strlen(b) > 0) strncpy(rec->emergencycontact, b, sizeof(rec->emergencycontact)-1);

    calculatebmi(rec);
    printf("✔ Member '%s' updated.\n", rec->name);
}

/* --------------------------- Delete Member --------------------------- */

health* deletemember(health *h, int *n, int idx) {
    if (!h || *n <= 0 || idx < 0 || idx >= *n) {
        printf("Error: invalid index for deletion.\n");
        return h;
    }
    printf("Deleting member '%s'...\n", h[idx].name);
    for (int i = idx; i < *n - 1; ++i) {
        h[i] = h[i+1];
    }
    (*n)--;
    health *tmp = realloc(h, (*n) * sizeof(health));
    if (!tmp && *n > 0) {
        printf("Warning: memory reallocation failed after deletion. Keeping old pointer.\n");
        return h;
    }
    printf("✔ Member deleted. Remaining members: %d\n", *n);
    return tmp ? tmp : h;
}

/* --------------------------- Search Member --------------------------- */

int searchmemberbyname(health *h, int n, const char *query) {
    if (!h || n <= 0) return -1;
    char qlower[128];
tolowertrim(query, qlower, sizeof(qlower));
    for (int i = 0; i < n; ++i) {
        char nlower[128];
        tolowertrim(h[i].name, nlower, sizeof(nlower));
        if (strstr(nlower, qlower)) return i;
    }
    return -1;
}
void displaymemberverbose(const health *r) {
    printf("\n------------------------------------------------------------\n");
    printf("Name: %s\n", r->name);
    printf("Age: %d years\n", r->age);
    printf("Weight: %.2f kg  Height: %.2f m\n", r->weight, r->height);
    printf("BMI: %.2f  (Category: %s)\n", r->bmi, getbmicategory(r->bmi));
    printf("Blood Pressure: %.2f / %.2f mmHg  (Category: %s)\n",
           r->bp_sys, r->bp_dia, getbpcategory(r->bp_sys, r->bp_dia));
    printf("Heart Rate: %.2f bpm  (Normal ~60-100 bpm)\n", r->heartrate);

    printf("\n-- Lab-like self-reported values --\n");
    printf("Fasting sugar: %.2f mg/dL    Post-meal sugar: %.2f mg/dL    (Category: %s)\n",
           r->fastingsugar, r->postmealsugar, getsugarcategory(r->fastingsugar, r->postmealsugar));
    printf("Cholesterol: %.2f mg/dL  (Category: %s)\n", r->cholesterol, getcholcategory(r->cholesterol));

    printf("\n-- Mental health tests --\n");
    printf("GAD-7 (Anxiety) Score: %d    Category: %s\n", r->anxietyscore, r->anxietycategory);
    printf("PHQ-9 (Depression) Score: %d    Category: %s\n", r->depressionscore, r->depressioncategory);

    printf("\n-- Sleep Tracking --\n");
    printf("Average sleep hours: %.2f    Sleep cycles (approx): %d\n", r->sleephours, r->sleepcycles);
    printf("Sleep quality summary: %s\n", r->sleepquality);
    printf("Sleep explanation: %s\n", r->sleepexplanation);

    printf("\n-- Medications / Allergies / Emergency --\n");
    printf("Medications: %s\n", r->medications);
    printf("Allergies: %s\n", r->allergies);
    printf("Emergency contact: %s\n", r->emergencycontact);
    printf("\n");
}

void displayallverbose(health *h, int n) {
    if (n <= 0 || h == NULL) {
        printf("No records to display.\n");
        return;
    }
    for (int i = 0; i < n; ++i) displaymemberverbose(&h[i]);
}

int main(void) {
    char b[512];
    int p = 0;

    printf("Family Health Tracker \n");
    printf("This program stores family health profiles, runs standard mental health tests (GAD-7, PHQ-9),\n");
    printf("and evaluates sleep using both age-based recommendations and approximate sleep cycles.\n\n");

    p = readintsafe("Enter number of family members to register initially (0 to start empty): ", b);

    health *h = NULL;
    if (p > 0) {
        h = malloc(p * sizeof(health));
        if (!h) {
            printf("Error: memory allocation failed. Exiting.\n");
            return 1;
        }
     }
    int n = p;

    for (int i = 0; i < n; ++i) {
        printf("\n--- Enter details for member %d of %d ---\n", i+1, n);
        readlinesafe("Name: ", h[i].name, sizeof(h[i].name), b);
        h[i].age = readintsafe("Age (years): ", b);
        h[i].weight = readfloatsafe("Weight (kg): ", b);
        h[i].height = readfloatsafe("Height (m): ", b);
        h[i].bp_sys = readfloatsafe("Systolic BP (mmHg): ", b);
        h[i].bp_dia = readfloatsafe("Diastolic BP (mmHg): ", b);
        h[i].heartrate = readfloatsafe("Heart rate (bpm): ", b);
        h[i].fastingsugar = readfloatsafe("Fasting blood sugar (mg/dL): ", b);
        h[i].postmealsugar = readfloatsafe("Post-meal blood sugar (mg/dL): ", b);
        h[i].cholesterol = readfloatsafe("Total cholesterol (mg/dL): ", b);

        for (int q = 0; q < 7; ++q) h[i].gad7[q] = 0;
        h[i].anxietyscore = 0;
        strcpy(h[i].anxietycategory, "Not taken");
        for (int q = 0; q < 9; ++q) h[i].phq9[q] = 0;
        h[i].depressionscore = 0;
        strcpy(h[i].depressioncategory, "Not taken");

        h[i].sleephours = readfloatsafe("Average sleep hours per night: ", b);
        h[i].sleepcycles = readintsafe("Approx. number of sleep cycles per night (integer): ", b);
        evaluatesleepcombined(&h[i]);

        readlinesafe("Medications (comma separated or 'None'): ", h[i].medications, sizeof(h[i].medications), b);
        readlinesafe("Allergies (comma separated or 'None'): ", h[i].allergies, sizeof(h[i].allergies), b);
        readlinesafe("Emergency contact (phone or name): ", h[i].emergencycontact, sizeof(h[i].emergencycontact), b);   

        calculatebmi(&h[i]);

        printf("\nTake mental health tests now for %s? (1=Anxiety, 2=Depression, 3=Both, 0=None): ", h[i].name);
        if (!fgets(b, sizeof(b), stdin)) { }
        else {
            int tc = 0;
            if (sscanf(b, "%d", &tc) == 1) {
                if (tc == 1) rungad7(&h[i], b, &p);
                else if (tc == 2) runphq9(&h[i], b, &p);
                else if (tc == 3) { rungad7(&h[i], b, &p); runphq9(&h[i], b, &p); }
            }
        }
    }
    /* --------------------------- MAIN MENU LOOP --------------------------- */
    while (1) {
        printf("\n\n============= MAIN MENU =============\n");
        printf("1. Display all records (verbose)\n");
        printf("2. Add a new member\n");
        printf("3. Update a member\n");
        printf("4. Delete a member\n");
        printf("5. Search a member by name\n");
        printf("6. Run Anxiety (GAD-7) test for a member\n");
        printf("7. Run Depression (PHQ-9) test for a member\n");
        printf("8. Evaluate/Update Sleep for a member\n");
        printf("9. Save all records to detailed text file\n");
        printf("10. Export all records to CSV\n");
        printf("11. Exit\n");

        p = readintsafe("Enter your choice (1-11): ", b);

        if (p == 1) {
            displayallverbose(h, n);
        }
        else if (p == 2) {
            h = addmember(h, &n, b, &p);
        }
        else if (p == 3) {
            readlinesafe("Enter name (part or full) to update: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) updatemember(h, idx, b, &p);
            else printf("Member not found for '%s'.\n", b);
        }
        else if (p == 4) {
            readlinesafe("Enter name (part or full) to delete: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) h = deletemember(h, &n, idx);
            else printf("Member not found for '%s'.\n", b);
        }
        else if (p == 5) {
            readlinesafe("Enter name (part or full) to search: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) displaymemberverbose(&h[idx]);
            else printf("Member not found for '%s'.\n", b);
        }
        else if (p == 6) {
            readlinesafe("Enter member name to run GAD-7: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) rungad7(&h[idx], b, &p);
            else printf("Member not found for '%s'.\n", b);
        }
        else if (p == 7) {
            readlinesafe("Enter member name to run PHQ-9: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) runphq9(&h[idx], b, &p);
            else printf("Member not found for '%s'.\n", b);
        }
        else if (p == 8) {
            readlinesafe("Enter member name to evaluate/update sleep: ", b, sizeof(b), b);
            int idx = searchmemberbyname(h, n, b);
            if (idx >= 0) {
                displaymemberverbose(&h[idx]);
                float newhours = readfloatsafe("New sleep hours (or enter same value): ", b);
                int newcycles = readintsafe("New sleep cycles (or enter same value): ", b);
                h[idx].sleephours = newhours;
                h[idx].sleepcycles = newcycles;
                evaluatesleepcombined(&h[idx]);
                printf("✔ Sleep updated for %s: %s\n", h[idx].name, h[idx].sleepquality);
            } else {
                printf("Member not found for '%s'.\n", b);
            }
        }
        else if (p == 10) {
            exportalltocsv(h, n);
        }
        else if (p == 11) {
            printf("Exiting. Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Please select 1..11.\n");
        }
    }

    if (h) free(h);
    return 0;
}