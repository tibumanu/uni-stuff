import request from 'supertest';
import express from 'express';
import { getElements, getElement, createElement, updateElement, deleteElement, getFilteredElements } from '../controllers/elements';
import ElementModel from '../models/element';
import elementsRoutes from "../routes/elements";
import mongoose from 'mongoose';
import { getAllIdeas, getIdea, addIdea, updateIdea, deleteIdea, getFilteredIdeas } from '../services/elements.service';

let mongoseConnection: typeof mongoose;

const app = express();

beforeAll(async () => {
mongoseConnection = await mongoose.connect("mongodb+srv://jaevski:g1g5DYIT2dwA5ohF@cluster0.rfdt0hp.mongodb.net/testDB");
//const app = express();

const router = express.Router()

app.use(express.json())

router.get("/", getAllIdeas);

router.get("/:elementId", getElement);

router.post("/", createElement);

router.put("/:elementId", updateElement);

router.delete("/:elementId", deleteIdea);
router.get("/filter/:smth", getFilteredElements);
app.use("/", router);
});

//jest.mock('../models/element');

describe('Elements Controller', () => {
    // afterEach(() => {
    //     jest.resetAllMocks();
    // });

    it('should update an element', async () => {
        const updatedElement = { title: 'test', desc: 'This is the fourth idea', gravity: 5 };
        // make new json object for the updated element
        // ElementModel.findById(updatedElement);
        const res = await request(app).put('/662152e72ce7036fb8f260aa').send(updatedElement);
        expect(res.statusCode).toEqual(200);
        expect(res.body).toEqual(updatedElement);
    });

    // it('should get all elements', async () => {
    //     const res = await request(app).get('/');
    //     console.log(res);
    //     expect(res.statusCode).toEqual(200);
    //     expect(res.body).toEqual(getAllIdeas());
    // });
    it('should get a single element', async () => {
        const mockElement = { title: 'test', desc: 'This is the fourth idea', gravity: 5 };
        // ElementModel.findById(mockElement);
        const res = await request(app).get('/662152e72ce7036fb8f260aa');
        expect(res.statusCode).toEqual(200);
        expect(res.body).toEqual(mockElement);
    });
    it('should create a new element', async () => {
        const newElement = { title: 'test!!!!!!!', desc: 'This is the nth idea', gravity: 67 };
        // ElementModel.create = jest.fn().mockResolvedValue(newElement);
        const res = await request(app).post('/').send(newElement);
        expect(res.statusCode).toEqual(201);
        expect(res.body).toEqual(newElement);
    });
    
    it('should get filtered elements', async () => {
        const elements = [{
            title: "Idea 2",
            desc: "This is the second idea",
            gravity: 2
        }];
        const res = await request(app).get('/filter/cond');
        expect(res.statusCode).toEqual(200);
        expect(res.body).toEqual(elements);
    });
});

// it('should get a single element', async () => {
//     const mockElement = { _id: '1', title: 'test', desc: 'test', gravity: 1 };
//     ElementModel.findById(mockElement);
//     const res = await request(app).get('/api/elements/660e9db3e176bb122ab9e5c5');
//     expect(res.statusCode).toEqual(200);
//     expect(res.body).toEqual(mockElement);
// });

//   it('should create a new element', async () => {
//     const newElement = { title: 'test', desc: 'test', gravity: 1 };
//     ElementModel.create = jest.fn().mockResolvedValue(newElement);
//     const res = await request(app).post('/api/elements').send(newElement);
//     expect(res.statusCode).toEqual(201);
//     expect(res.body).toEqual(newElement);
//   });

//   it('should update an element', async () => {
//     const updatedElement = { _id: '1', title: 'updated', desc: 'updated', gravity: 2 };
//     ElementModel.findById(updatedElement);
//     const res = await request(app).put('/api/elements/1').send(updatedElement);
//     expect(res.statusCode).toEqual(200);
//     expect(res.body).toEqual(updatedElement);
//   });

//   it('should delete an element', async () => {
//     const mockElement = { _id: '1', title: 'test', desc: 'test', gravity: 1, deleteOne: jest.fn() };
//     ElementModel.findById(mockElement);
//     const res = await request(app).delete('/api/elements/1');
//     expect(res.statusCode).toEqual(204);
//     expect(mockElement.deleteOne).toHaveBeenCalled();
//   });
