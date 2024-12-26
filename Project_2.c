#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures for users and their connections
typedef struct FriendNode {
    struct User *user;
    struct FriendNode *next;
} FriendNode;

typedef struct User {
    char name[30];
    FriendNode *friends; // Linked list of friends
    struct User *next;   // Linked list of all users
} User;

// Head of the user list
User *userHead = NULL;

// Function to create a new user
User *createUser(char *name) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->name, name);
    newUser->friends = NULL;
    newUser->next = NULL;
    return newUser;
}

// Add user to the user list
void addUser(char *name) {
    User *newUser = createUser(name);
    newUser->next = userHead;
    userHead = newUser;
    printf("User %s added.\n", name);
}
  
// Find a user by name
User *findUser(char *name) {
    User *temp = userHead;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add friend connection
void addFriend(User *user1, User *user2) {
    FriendNode *newFriend1 = (FriendNode *)malloc(sizeof(FriendNode));
    newFriend1->user = user2;
    newFriend1->next = user1->friends;
    user1->friends = newFriend1;

    FriendNode *newFriend2 = (FriendNode *)malloc(sizeof(FriendNode));
    newFriend2->user = user1;
    newFriend2->next = user2->friends;
    user2->friends = newFriend2;

    printf("%s and %s are now friends.\n", user1->name, user2->name);
}

// Display mutual friends between two users
void displayMutualFriends(User *user1, User *user2) {
    printf("Mutual friends of %s and %s:\n", user1->name, user2->name);
    FriendNode *friends1 = user1->friends;
    while (friends1 != NULL) {
        FriendNode *friends2 = user2->friends;
        while (friends2 != NULL) {
            if (friends1->user == friends2->user) {
                printf("%s\n", friends1->user->name);
            }
            friends2 = friends2->next;
        }
        friends1 = friends1->next;
    }
}

// Suggest new friends based on mutual friends
void suggestNewFriends(User *user) {
    FriendNode *friend = user->friends;
    printf("Friend suggestions for %s:\n", user->name);

    while (friend != NULL) {
        FriendNode *friendsFriend = friend->user->friends;
        while (friendsFriend != NULL) {
            // Ensure it's not already a friend of the user
            FriendNode *temp = user->friends;
            int isAlreadyFriend = 0;
            while (temp != NULL) {
                if (temp->user == friendsFriend->user) {
                    isAlreadyFriend = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!isAlreadyFriend && strcmp(friendsFriend->user->name, user->name) != 0) {
                printf("Suggested: %s\n", friendsFriend->user->name);
            }

            friendsFriend = friendsFriend->next;
        }
        friend = friend->next;
    }
}

// Main function with a while loop
int main() {
    int choice = 0;
    char name1[30], name2[30];
    User *user1, *user2;

    while (choice != 5) {
        printf("\nMenu:\n");
        printf("1. Add User\n");
        printf("2. Add Friend\n");
        printf("3. Display Mutual Friends\n");
        printf("4. Suggest New Friends\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the user: ");
                scanf("%s", name1);
                addUser(name1);
                break;
            case 2:
                printf("Enter the name of the first user: ");
                scanf("%s", name1);
                printf("Enter the name of the second user: ");
                scanf("%s", name2);
                user1 = findUser(name1);
                user2 = findUser(name2);
                if (user1 && user2) {
                    addFriend(user1, user2);
                } else {
                    printf("One or both users not found.\n");
                }
                break;
            case 3:
                printf("Enter the name of the first user: ");
                scanf("%s", name1);
                printf("Enter the name of the second user: ");
                scanf("%s", name2);
                user1 = findUser(name1);
                user2 = findUser(name2);
                if (user1 && user2) {
                    displayMutualFriends(user1, user2);
                } else {
                    printf("One or both users not found.\n");
                }
                break;
            case 4:
                printf("Enter the name of the user: ");
                scanf("%s", name1);
                user1 = findUser(name1);
                if (user1) {
                    suggestNewFriends(user1);
                } else {
                    printf("User not found.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
