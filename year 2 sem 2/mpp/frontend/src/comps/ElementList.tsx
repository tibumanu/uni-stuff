import { useState } from "react";
import { IElement } from "./Element.type";
import { ISubElement } from "./Element.type";
import "./ElementList.style.css";
import ElementModal from "./ElementModal";
import axios from 'axios';

type Props = {
    list: IElement[];
    onDeleteClickHandle: (data: IElement) => void;
    onEdit: (data: IElement) => void;
}

export const ElementList = (props: Props) => {

    const { list, onDeleteClickHandle, onEdit } = props;

    const [showModal, setShowModal] = useState(false);
    const [dataToShow, setDataToShow] = useState(null as IElement | null);
    
    // const viewElement = (data: IElement) => {
    //   console.log(data);
    //  setDataToShow(data);
    //   setShowModal(true);
    // }

    const viewElement = async (el: IElement) => {
      try {
          const elementId = el.id;
          // Make an API call to fetch the element data along with its children
          const response = await axios.get(`/api/elements/totalelement/${elementId}`);
          const { element, children } = response.data;

        // Combine element and children data
        const elementData: IElement = {
            id: element._id,
            title: element.title,
            desc: element.desc,
            gravity: element.gravity,
            children: children.map((child: any) => ({
                id: child._id,
                desc: child.desc,
                rating: child.rating
            }))
        };

        // Set the fetched data to the state
        setDataToShow(elementData);
        setShowModal(true);
          setShowModal(true);
      } catch (error) {
          console.error('Error fetching element data:', error);
      }
  };

    const testFunction = () => {
        console.log("test");
    }

    const onCloseModal = () => {
        setShowModal(false);
    }

    return (
      <div>
        <table>
          <tbody>
            <tr>
              <th>ID</th>
              <th>TITLE</th>
              <th>DESCRIPTION</th>
              <th>GRAVITY</th>
              <th>Action</th>
            </tr>
            {list.map((el) => (
              <tr key={el.id}>
                <td>{`${el.id}`}</td>
                <td>{`${el.title}`}</td>
                <td>{`${el.desc}`}</td>
                <td>{`${el.gravity}`}</td>
                <td>
                  <div className="actionButtons">
                    <input
                      className="actionButton"
                      type="button"
                      value="View"
                      onClick={() => viewElement(el)}
                    />
                    <input
                      className="actionButton"
                      type="button"
                      value="Edit"
                      onClick={() => onEdit(el)}
                    />
                    <input
                      className="actionButton"
                      type="button"
                      value="Delete"
                      onClick={() => onDeleteClickHandle(el)}
                    />
                  </div>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
        {showModal && dataToShow !== null && (
          <ElementModal onClose={onCloseModal} data={dataToShow} />
        )}
      </div>
    );
};

export default ElementList;