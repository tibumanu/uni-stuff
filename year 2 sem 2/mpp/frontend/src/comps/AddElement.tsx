import { IElement } from "./Element.type";
import "./ElementForm.style.css"
import { useState } from "react";

type Props = {
    onBackButtonClickHandle : () => void;
    onSubmitClickHandle : (data: IElement) => void;
}

const AddElement = (props: Props) => {
    
    const[id, setId] = useState("");
    const[title, setTitle] = useState("");
    const[desc, setDesc] = useState("");
    const[gravity, setGravity] = useState(1);
    
    const {onBackButtonClickHandle, onSubmitClickHandle} = props
    const onIdChangeHandle = (e: any) => {
        setId(e.target.value)
    }
    const onTitleChangeHandle = (e: any) => {
        setTitle(e.target.value)
    }
    const onDescChangeHandle = (e: any) => {
        setDesc(e.target.value)
    }
    const onGravityChangeHandle = (e: any) => {
        setGravity(e.target.value)
    }
    const onSubmitButtonClickHandle = (e: any) => {
        e.preventDefault();
        const data: IElement = {
            id: id,
            title: title,
            desc: desc,
            gravity: gravity,
        }
        onSubmitClickHandle(data);
        
    }
    return (
        
        <div className="form-container">
            <p>ADD ELEMENT</p>
        <form onSubmit={onSubmitButtonClickHandle}>
            <div>
                <label htmlFor="inputId">
                    ID: &nbsp;
                </label>
                <input id ="inputId" type="text" value={id} onChange={onIdChangeHandle}/>

            </div>
            <div>
                <label htmlFor="inputTitle" >
                    TITLE:
                </label>
                <input id="inputTitle" type="text" value={title} onChange={onTitleChangeHandle}/>

            </div>
            <div>
                <label htmlFor="inputDesc">
                    DESC:
                </label>
                <input id = "inputDesc" type="text" value={desc} onChange={onDescChangeHandle}/>

            </div>
            <div>
                <label htmlFor="inputGravity">
                    GRAVITY:
                </label>
                <input id="inputGravity" type="number" value={gravity} onChange={onGravityChangeHandle}/>

            </div>
            <div>
                <label>
                    <input type="button" value="BACK" onClick={onBackButtonClickHandle}/>
                    <input type="submit" value="ADD"/>
                </label>
            </div>
            
        </form>
        </div>
    )
}

export default AddElement;