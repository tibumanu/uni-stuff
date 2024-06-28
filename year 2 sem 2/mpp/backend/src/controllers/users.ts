import { RequestHandler } from "express";
import createHttpError from "http-errors";
import UserModel from "../models/user";
import bcrypt from "bcrypt";

interface SignUpBody{
    username?: string,
    email?: string,
    password?: string
}


export const getAuthenticatedUser: RequestHandler = async (req, res, next) => {
    const authenticatedUserId = req.session.userId;

    try{
        if(!authenticatedUserId){
            throw createHttpError(403, "Not authenticated.");
        }
        const user = await UserModel.findById(authenticatedUserId).select("+email").exec();
        res.status(200).json(user);
    }catch(error){
        next(error);
    }
}

export const signUp: RequestHandler<unknown, unknown, SignUpBody> = async (req, res, next) => {
    const username = req.body.username;
    const email = req.body.email;
    const passwordRaw = req.body.password;
    try{
        if(!username || !email || !passwordRaw){
            throw createHttpError(400, "Parameters missing.");
        }
    const existingUsername = await UserModel.findOne({username: username}).exec();
    if(existingUsername){
        throw createHttpError(409, "Username already taken.");
    }
    const existingEmail = await UserModel.findOne({email: email}).exec();
    if(existingEmail){
        throw createHttpError(409, "Email already taken.");
    }
    const passwordHashed = await bcrypt.hash(passwordRaw, 10);

    const newUser = await UserModel.create({username, email, password: passwordHashed});

    req.session.userId = newUser._id;

    res.status(201).json(newUser);
    }catch(error){
        next(error);
    }
}

interface LoginBody{
    username?: string,
    password?: string

}

export const login: RequestHandler<unknown, unknown, LoginBody, unknown> = async (req, res, next) => {
    const username = req.body.username;
    const password = req.body.password;

    try{
        if(!username || !password){
            throw createHttpError(400, "Parameters missing.");
        }

        const user = await UserModel.findOne({username: username}).select("+password +email").exec();
        if(!user){
            throw createHttpError(404, "User not found.");
            throw createHttpError(401, "Invalid credentials.");
        }
        const pwdMatch = await bcrypt.compare(password, user.password);
        if(!pwdMatch){
            throw createHttpError(401, "Invalid credentials.");
        }

        req.session.userId = user._id;
        res.status(200).json(user);
    }catch(error){
        next(error);
    }
}

export const logout: RequestHandler = async (req, res, next) => {
    req.session.destroy((err) => {
        if(err){
            next(err);
        }
        res.sendStatus(204);
    });
}