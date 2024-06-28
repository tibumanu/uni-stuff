export class ElementChild{
    thoughtID: number;
    parentID: string;
    desc: string;
    rating: number;

    constructor(thoughtID: number, parentID: string, desc: string, rating: number){
        this.thoughtID = thoughtID;
        this.parentID = parentID;
        this.desc = desc;
        this.rating = rating;
    }
}