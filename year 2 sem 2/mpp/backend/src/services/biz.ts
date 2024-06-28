import { RequestHandler } from 'express';
import { } from './elements.service';

export const getAllIdeas = () => {
    return [
        { title: 'test', desc: 'This is the first idea', gravity: 1 },
        { title: 'test', desc: 'This is the second idea', gravity: 2 },
        { title: 'test', desc: 'This is the third idea', gravity: 3 },
        { title: 'test', desc: 'This is the fourth idea', gravity: 4 },
        { title: 'test', desc: 'This is the fifth idea', gravity: 5 },
        { title: 'test', desc: 'This is the sixth idea', gravity: 6 },
        { title: 'test', desc: 'This is the seventh idea', gravity: 7 },
        { title: 'test', desc: 'This is the eighth idea', gravity: 8 },
        { title: 'test', desc: 'This is the ninth idea', gravity: 9 },
        { title: 'test', desc: 'This is the tenth idea', gravity: 10 },
    ];
};

// export const getFiltered: RequestHandler = (req, res, next) => {
    
// }