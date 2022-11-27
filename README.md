# Console-Login-Application

**Regestration and Login System..**  

Made by: [***Youssef Morad***](https://github.com/YoussefMorad1) -
[***Nour Wael***](https://github.com/nourelshaer) -
[***Nour Tarek***](https://github.com/NourTarek201)   
Requested by: *Dr. Mohammed El-Ramly* in Structured Programming course (Assingment 4)

## System Details  
**System has a menu that asks the user if he wants to:**  
1. Register  
2. Login  
3. Change Password  
4. Exit

<img src = "https://user-images.githubusercontent.com/102534922/204149880-c1309d04-8aa0-4bcf-b080-d53593b71510.png" width = 600>

## User Registration Details
1. A new user can register and add his profile (with personal information) to the system and select a username and a password.  
  
2. System checks new user's ID and email weren't not be previously registered in the system by other users,  
If either of them is registered, the system refuses them and ask user to enter new ones   
  
3. Checking that email follows proper email format, mobile number follows the Egyptian format and the name follows proper format   
  
4. Display a message to the user of what letters are allowed/required and conditions that must apply to the password.  
  
5. Ask the user to repeat the password and make sure it was entered the same twice.  
  
6. Verifying that the password is a strong one. If not, it displays to the user a message and ask him for another password.  
  
7. Covering the password with ' *** ' while the user is entering it.  
  
8. If registration is valid, the user profile, ID and password are added to the list of system users and stored in the user file.  
  
9. Passwords are stored encrypted.  

## User Login
1. To login, a user enters his ID and password. Password is still covered with " *** " while being entered. If the ID matches an ID of a register user, and the password is correct, a message is displayed saying like "Successful login, welcome -his name-"   
  
2. If login fails, a massage is displayed that says "Failed login. Try again."  

3. The user is given three trials in total, after them, a message is displayed that informs him that he is denied access to the system. Then he returns to the main menu.   

## Change Password
If the user wants to change the password:
  * S/he should choose this option and then login.
  * Enter his old password.
  * Enter the newly desired password.
  * Then enter the new password again and it should match the first time he entered it
  * The same message, rules, etc. of entering a new strong password should apply.
  * The newly selected password SHOULD NOT be any of his old passwords (this means
  that older passwords should be stored)
  * Then his profile is updated with the new password and it stored encrypted
