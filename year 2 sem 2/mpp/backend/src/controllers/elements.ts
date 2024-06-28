import { RequestHandler } from "express";
import ElementModel from "../models/element";
import createHttpError from "http-errors";
import mongoose from "mongoose";
import {getAllIdeas, getIdea, addIdea, updateIdea, deleteIdea, getFilteredIdeas} from "../services/elements.service";
import ChildModel from "../models/elementChild";

export const getElements: RequestHandler = async (_req, res, next) => {
    try{
      const elements = await ElementModel.find().exec();
      //const elements = getAllIdeas();
      res.status(200).json(elements);
  
    }catch(error){
       next(error);
    }
  };

export const getSortedElements: RequestHandler = async (_req, res, next) => {
    try{
      const elements = (await ElementModel.find().exec()).sort((a, b) => b.gravity - a.gravity);
      //const elements = getSortedIdeas();
      res.status(200).json(elements);
  
    }catch(error){
       next(error);
    }
  }

export const getElement: RequestHandler = async (req, res, next) => {
    const elementId = req.params.elementId;
    try{
         if(!mongoose.Types.ObjectId.isValid(elementId)){
             throw createHttpError(400, "Invalid Element ID");
         }
         const element = await ElementModel.findById(elementId).exec();
        // const element = getIdea('test');
        if(!element){
            throw createHttpError(404, "Element not found");
        }
        res.status(200).json(element);
        }catch(error){
        next(error);
        }
};

export const getFilteredElements: RequestHandler = async (req, res, next) => {
    try{
        //const elements = await ElementModel.find({title: req.params.smth}).exec();
        const elements = await ElementModel.find({title: {$regex: req.params.smth, $options: 'i'}}).exec();
        //const elements = getFilteredIdeas(req.params.smth);
      res.status(200).json(elements);
  
    }catch(error){
       next(error);
    }
  };

  export const getGamesByPageServer: RequestHandler = async (req, res, next) => {
    try{
        const currentPage = parseInt(req.query.page as string);
        const recordsPerPage = parseInt(req.query.records as string);
        const elements = await ElementModel.find().exec();
       /// const elements = getFromServer();
        const indexOfLastRecord = currentPage * recordsPerPage;
        const indexOfFirstRecord = indexOfLastRecord - recordsPerPage;
        const currentRecords = elements.slice(indexOfFirstRecord, indexOfLastRecord);
        const totalPages = Math.ceil(elements.length / recordsPerPage);
        res.status(200).json({currentRecords, totalPages});
    }catch(error){
        next(error);
  }
};

export const updateElement: RequestHandler<updateElementParams, unknown, updateElementBody, unknown> = async (req, res, next) => {
    const elementId = req.params.elementId;
    const {title, desc, gravity} = req.body;
    try{
        if(!mongoose.Types.ObjectId.isValid(elementId)){
            throw createHttpError(405, "Invalid Element ID");
        }
        
        if(!title || !gravity){
            throw createHttpError(400, "Element requires both title and gravity.");
        }
        if(!title && !desc && !gravity){
            throw createHttpError(400, "Element requires at least one field to update");
        }
        const element = await ElementModel.findById(elementId).exec();
       // const element = getIdea('test');
        if(!element){
            throw createHttpError(405, "Element n!!!!ot found");
        }
        if(title){
            element.title = title;
        }
        if(desc){
            element.desc = desc;
        }
        if(gravity){
            element.gravity = gravity;
        }
        const result = await element.save();
        res.status(200).json(element);
       // res.status(200).json({title: element.title, desc: element.desc, gravity: element.gravity});

    }catch(error){
        next(error);
    }};

export const getChartData: RequestHandler = async (_req, res, next) => {
    // // group elements by gravity
    // const groupedData = elements.reduce((acc, element) => {
    //     const { gravity } = element;
    //     if (!acc[gravity]) {
    //       acc[gravity] = 1;
    //     } else {
    //       acc[gravity]++;
    //     }
    //     return acc;
    //   }, {});
    // above code is from the front end; this should be done here, in the back end; the front end should only receive the data
    try {
        const elements = await ElementModel.find().exec();
        const groupedData: { [gravity: number]: number } = elements.reduce((acc: { [gravity: number]: number }, element) => {
            const { gravity } = element;
            if (!acc[gravity]) {
                acc[gravity] = 1;
            } else {
                acc[gravity]++;
            }
            return acc;
        }, {});
        res.status(200).json(groupedData);
    } catch (error) {
        next(error);
    }
};

export const deleteElement: RequestHandler<updateElementParams, unknown, unknown, unknown> = async (req, res, next) => {
    const elementId = req.params.elementId;
    try{
        if(!mongoose.Types.ObjectId.isValid(elementId)){
            throw createHttpError(400, "Invalid Element ID");
        }
        const element = await ElementModel.findById(elementId).exec();
        if(!element){
            throw createHttpError(404, "Element not found");
        }
        
        await element.deleteOne();
        res.status(204).json(element);
    }catch(error){
        next(error);
    }
};


export const createElement: RequestHandler<unknown, unknown, CreateElementBody, unknown> = async (req, res, next) => {
    const {title, desc, gravity} = req.body;

    try{

        if(!title || !gravity){
            throw createHttpError(400, "Element requires both title and gravity.");
        }

       const newElement = await ElementModel.create({title: title, desc: desc, gravity: gravity});
       // const newElement = {title, desc, gravity};
      const result = await newElement.save();
      res.status(201).json(result);

    }catch(error){
      next(error);
    }
  };

export const getTotalElement: RequestHandler = async (_req, res, next) => {
    // we'll get the element, alongside its children
    // we'll get the element, alongside its children
    try {
        const elementId = _req.params.elementId;
        const element = await ElementModel.findById(elementId).exec();
        if(!element){
            throw createHttpError(404, "Element not found");
        }
        const children = await ChildModel.find({parentID: elementId}).exec();
        res.status(200).json({element, children});
    } catch (error) {
        next(error);
    }
};

interface CreateElementBody{
    title?: string;
    desc?: string;
    gravity?: number;

}


interface updateElementParams{
    elementId: string;
    title?: string;
    desc?: string;
    gravity?: number;

}

interface updateElementBody{
    title?: string;
    desc?: string;
    gravity?: number;

}




