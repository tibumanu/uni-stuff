import ElementChildModel from "../models/elementChild";
import { ElementChild } from "../models/elementChild.class";

export class ThoughtRepository{
    constructor(    ){}

    async addThought(parentID: string, desc: string, rating: number){
        const newThought = await ElementChildModel.create({thoughtID, parentID, desc, rating});
        await newThought.save();
        return newThought;
    }
    
    async deleteThought(thoughtID: number){
        const thought = await ElementChildModel.findOneAndDelete({thoughtID});
    }

    async getThought(thoughtID: number){
        const thought = await ElementChildModel.findOne({
            thoughtID
        });
        return thought;
    }
    async getAllThoughts(){
        const thoughts = await ElementChildModel.find({});
        return thoughts;
    }
}