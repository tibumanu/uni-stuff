
import { User } from "../models/user";

export async function getLoggedInUser() {
    const response = await fetch('/api/users', {method: "GET"});
    return response.json();
}

export interface SignUpCredentials {
    username: string,
    email: string,
    password: string;
}

export async function signUp(credentials: SignUpCredentials): Promise<User>{
    const response = await fetch('/api/users/signup', {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(credentials)
    });
    return response.json();
}

export interface LogInCredentials{
    email: string;
    password: string;
}

export async function logIn(credentials: LogInCredentials): Promise<User>{
    const response = await fetch('/api/users/login', {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(credentials)
    });
    return response.json();
}

export async function logOut(){
    const response = await fetch('/api/users/logout', {method: "POST"});
    return response.json();
}