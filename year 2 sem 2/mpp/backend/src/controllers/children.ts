import { RequestHandler } from 'express';
import ChildModel from '../models/elementChild';
import createHttpError from 'http-errors';
import mongoose from "mongoose";

export const getChildren: RequestHandler = async (_req, res, next) => {
    try {
        const children = await ChildModel.find().exec();
        res.status(200).json(children);
    } catch (error) {
        next(error);
    }
}

export const getChild: RequestHandler = async (req, res, next) => {
    const childId = req.params.childId;
    try {
        if (!mongoose.Types.ObjectId.isValid(childId)) {
            throw createHttpError(400, "Invalid Child ID");
        }
        const child = await ChildModel.findById(childId).exec();
        if (!child) {
            throw createHttpError(404, "Child not found");
        }
        res.status(200).json(child);
    } catch (error) {
        next(error);
    }
}

export const createChild: RequestHandler = async (req, res, next) => {
    const desc = req.body.desc;
    const rating = req.body.rating;
    // get ParentID, which is of type Types.ObjectID
    const parentID = req.body.parentID;
    try{
        const newChild = await ChildModel.create({parentID, desc, rating});
        res.status(201).json(newChild);
    }catch(error){
        next(error);
    }
}

export const updateChild: RequestHandler = async (req, res, next) => {
    const childId = req.params.childId;
    const desc = req.body.desc;
    const rating = req.body.rating;
    try{
        if(!mongoose.Types.ObjectId.isValid(childId)){
            throw createHttpError(400, "Invalid Child ID");
        }
        const child = await ChildModel.findById(childId).exec();
        if(!child){
            throw createHttpError(404, "Child not found");
        }
        child.desc = desc;
        child.rating = rating;
        const updatedChild = await child.save();
        res.status(200).json(updatedChild);
    }catch(error){
        next(error);
    }
}

export const getChildrenByParentID: RequestHandler = async (req, res, next) => {
    const parentId = req.params.parentId;
    try{
        if(!mongoose.Types.ObjectId.isValid(parentId)){
            throw createHttpError(400, "Invalid Parent ID");
        }
        const children = await ChildModel.find({parentID: parentId}).exec();
        res.status(200).json(children);
    }catch(error){
        next(error);
    }
}

export const getParents: RequestHandler = async (_req, res, next) => {
    try{
        const parents = await ChildModel.distinct("parentID").exec();
        res.status(200).json(parents);
    }catch(error){
        next(error);
    }
}