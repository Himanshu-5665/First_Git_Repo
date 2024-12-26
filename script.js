class FriendNode {
    constructor(user) {
        this.user = user;
        this.next = null;
    }
}

class User {
    constructor(name) {
        this.name = name;
        this.friends = null;
    }
}

let userList = [];

// Function to create a new user
function createUser(name) {
    if (findUser(name) === null) {
        let newUser = new User(name);
        userList.push(newUser);
        return newUser;
    } else {
        return null;
    }
}

// Find a user by name
function findUser(name) {
    for (let user of userList) {
        if (user.name === name) {
            return user;
        }
    }
    return null;
}

// Add friend connection
function addFriendConnection(user1, user2) {
    if (user1 && user2 && user1 !== user2) {
        let newFriend1 = new FriendNode(user2);
        newFriend1.next = user1.friends;
        user1.friends = newFriend1;

        let newFriend2 = new FriendNode(user1);
        newFriend2.next = user2.friends;
        user2.friends = newFriend2;
    }
}

// Display mutual friends between two users
function findMutualFriends(user1, user2) {
    let mutualFriends = [];
    let friends1 = user1.friends;
    while (friends1) {
        let friends2 = user2.friends;
        while (friends2) {
            if (friends1.user === friends2.user) {
                mutualFriends.push(friends1.user.name);
            }
            friends2 = friends2.next;
        }
        friends1 = friends1.next;
    }
    return mutualFriends;
}

// Suggest new friends based on mutual friends
function suggestFriends(user) {
    let suggestions = [];
    let friend = user.friends;

    while (friend) {
        let friendsFriend = friend.user.friends;
        while (friendsFriend) {
            if (friendsFriend.user !== user) {
                suggestions.push(friendsFriend.user.name);
            }
            friendsFriend = friendsFriend.next;
        }
        friend = friend.next;
    }

    return suggestions;
}

// GUI Functions (modified to use console)
function addUser() {
    let name = document.getElementById("username").value;
    if (name) {
        let user = createUser(name);
        if (user) {
            console.log(`User ${name} added.`);
        } else {
            console.log(`User ${name} already exists.`);
        }
    }
}

function addFriend() {
    let name1 = document.getElementById("user1").value;
    let name2 = document.getElementById("user2").value;
    if (name1 && name2) {
        let user1 = findUser(name1);
        let user2 = findUser(name2);
        if (user1 && user2) {
            addFriendConnection(user1, user2);
            console.log(`${name1} and ${name2} are now friends.`);
        } else {
            console.log("One or both users not found.");
        }
    }
}

function displayMutualFriends() {
    let name1 = document.getElementById("user1").value;
    let name2 = document.getElementById("user2").value;
    if (name1 && name2) {
        let user1 = findUser(name1);
        let user2 = findUser(name2);
        if (user1 && user2) {
            let mutual = findMutualFriends(user1, user2);
            if (mutual.length > 0) {
                console.log(`Mutual friends: ${mutual.join(', ')}`);
            } else {
                console.log("No mutual friends found.");
            }
        } else {
            console.log("One or both users not found.");
        }
    }
}

function suggestNewFriends() {
    let name = document.getElementById("username1").value;
    if (name) {
        let user = findUser(name);
        if (user) {
            let suggestions = suggestFriends(user);
            if (suggestions.length > 0) {
                console.log(`Suggested friends: ${suggestions.join(', ')}`);
            } else {
                console.log("No new friend suggestions found.");
            }
        } else {
            console.log("User not found.");
        }
    }
}
