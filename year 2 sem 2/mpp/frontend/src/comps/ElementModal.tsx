// in ElementModal.tsx
import "./ElementModal.style.css";
import { IElement, ISubElement } from "./Element.type";

type Props = {
    onClose: () => void;
    data: IElement;
};

const ElementModal = (props: Props) => {
    const { onClose, data } = props;

    return (
        <div id="myModal" className="modal">
            <div className="modal-content">
                <span className="close" onClick={onClose}>&times;</span>
                <div>
                    <h3>ELEMENT DATA</h3>
                    <div>
                        <label>ID:</label>
                        <span>{data.id}</span>
                    </div>
                    <div>
                        <label>TITLE:</label>
                        <span>{data.title}</span>
                    </div>
                    <div>
                        <label>DESC:</label>
                        <span>{data.desc}</span>
                    </div>
                    <div>
                        <label>GRAVITY:</label>
                        <span>{data.gravity}</span>
                    </div>
                    {data.children && (
                        <div>
                            <h4>Sub Elements</h4>
                            <ul>
                                {data.children.map((subElement: ISubElement) => (
                                    <li key={subElement.id}>
                                        {subElement.desc} - {subElement.rating}
                                    </li>
                                ))}
                            </ul>
                        </div>
                    )}
                </div>
            </div>
        </div>
    );
};

export default ElementModal;
