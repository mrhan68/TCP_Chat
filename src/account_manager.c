/**
 * Account manager
 */
#include "account_manager.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Ghi dữ liệu từ linked-list vào file
 */
void write_to_file(Account *list)
{

    FILE *fp = fopen("../assets/account.txt", "w");

    if (fp)
    {
        Account *acc = list;
        while (acc)
        {
            fprintf(fp, "%s %s %d\n", acc->username, acc->password, acc->is_signed_in);
            acc = acc->next;
        }

        fclose(fp);
    }
    else
    {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }
}

void add_to_list(Account *list, Account *new_acc)
{

    // while(lastNode-> next != NULL){
    //     lastNode = lastNode->next;
    //     if(acc == NULL){
    //         acc->next = new_acc;
    //     }
    // }

    // if head is NULL, it is an empty list
    if (list == NULL)
        list = new_acc;
    // Otherwise, find the last node and add the newNode
    else
    {
        Account *lastNode = list;
        // last node's next address will be NULL.
        while (lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        // add the newNode at the end of the linked list
        lastNode->next = new_acc;
    }
    write_to_file(list);
}

/**
 * Đọc dữ liệu từ file
 * Tạo ra 1 linked-list lưu trữ các tài khoản
 * Trả về 1 con trỏ đến tài khoản đầu tiên
 */
Account *read_account_list()
{

    FILE *fp = fopen("../assets/account.txt", "r");

    Account *list = NULL;
    Account *prev_acc, *acc;

    char username[USERNAME_SIZE + 1];
    char password[PASSWORD_SIZE + 1];
    int status;

    if (fp)
    {
        while (!feof(fp))
        {
            // Đọc dữ liệu
            fscanf(fp, "%s", username);
            fscanf(fp, "%s", password);
            fscanf(fp, "%d", &status);

            // Kiểm tra dòng trống
            if (strlen(username) == 0)
            {
                continue;
            }

            // Lưu dữ liệu vào bộ nhớ
            acc = (Account *)malloc(sizeof(Account));
            strcpy(acc->username, username);
            strcpy(acc->password, password);
            acc->is_signed_in = 0;

            // Thêm vào danh sách
            if (list == NULL)
            {
                list = acc;
                prev_acc = acc;
            }
            else
            {
                prev_acc->next = acc;
                prev_acc = acc;
            }

            // Reset biến lưu dữ liệu
            strcpy(username, "");
            strcpy(password, "");
        }

        fclose(fp);
    }
    else
    {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }

    return list;
}

/**
 * Tìm kiếm tài khoản trong danh sách
 * - Tìm thấy: trả về tài khoản đó
 * - Không tìm thấy: trả về NULL
 */
Account *find_account(Account *list, char *username)
{

    Account *acc = list;

    while (acc)
    {
        if (strcmp(acc->username, username) == 0)
        {
            return acc;
        }
        acc = acc->next;
    }

    return NULL;
}
