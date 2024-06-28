import { useState } from "react";
import { IElement } from "./Element.type";
import "./ElementForm.style.css"

type Props = {
    data: IElement
    onBackButtonClickHandle: () => void;
    onUpdateClickHandle: (data: IElement) => void;
}

const EditElement = (props: Props) =>{
    const {data, onBackButtonClickHandle, onUpdateClickHandle} = props;

    const initialId = data?.id || "";
    const initialTitle = data?.title || "";
    const initialDesc = data?.desc || "";
    const initialGravity = data?.gravity || 1;

    const [id, setId] = useState(initialId);
    const [title, setTitle] = useState(initialTitle);
    const [desc, setDesc] = useState(initialDesc);
    const [gravity, setGravity] = useState(initialGravity);
    
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
        const updatedData: IElement = {
            id: id,
            title: title,
            desc: desc,
            gravity: gravity,
        }
        onUpdateClickHandle(updatedData);
        
    }
        
    return (
        
        <div className="form-container">
            <p>EDIT ELEMENT</p>
        <form onSubmit={onSubmitButtonClickHandle} style={{ display: "flex", justifyContent: "center", alignItems: "center"}}>
            <div>
                <label htmlFor="updateId">
                    ID: &nbsp;
                </label>
                <input id = "updateId" type="text" value={id} onChange={onIdChangeHandle}/>

            </div>
            <div>
                <label htmlFor="updateTitle">
                    TITLE:
                </label>
                <input id = "updateTitle" type="text" value={title} onChange={onTitleChangeHandle}/>

            </div>
            <div>
                <label htmlFor="updateDesc">
                    DESC:
                </label>
                <input id = "updateDesc" type="text" value={desc} onChange={onDescChangeHandle}/>

            </div>
            <div>
                <label htmlFor="updateGravity">
                    GRAVITY:
                </label>
                <input id = "updateGravity" type="number" value={gravity} onChange={onGravityChangeHandle} style={{minHeight: "50px", maxWidth: "50px"}}/>

            </div>
            <div>
                <label>
                    <input type="button" value="BACK" onClick={onBackButtonClickHandle}/>
                    <input type="submit" value="UPDATE"/>
                </label>
            </div>
            
        </form>
        </div>
    )
}

export default EditElement;