#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *file1, *file2;
    char line1[100], line2[100];
    file1 = fopen("my_details.txt", "w");
    fprintf(file1, "Name: Himanshu Raturi\nRoll: 31\nCity: Rishikesh\n");
    fclose(file1);
    file2 = fopen("friend_details.txt", "w");
    fprintf(file2, "Name: Akhil Bhatt\nRoll: 30\nCity: Rishikesh\n");
    fclose(file2);
    file1 = fopen("my_details.txt", "r");
    file2 = fopen("friend_details.txt", "r");
    while (fgets(line1, sizeof(line1), file1))
    {
        rewind(file2);
        while (fgets(line2, sizeof(line2), file2))
        {
            if (strcmp(line1, line2) == 0)
                printf("Common line: %s", line1);
        }
    }
    fclose(file1);
    fclose(file2);
    return 0;
}
