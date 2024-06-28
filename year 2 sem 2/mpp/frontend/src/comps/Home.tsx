import { useEffect, useState } from "react";
import { IElement, PageEnum, dummyElementList } from "./Element.type";
import "./Home.style.css"
import {ElementList} from "./ElementList";
import AddElement from "./AddElement";
import EditElement from "./EditElement";
import { sortAscByGravity, sortAscByTitle, sortDescByGravity, sortDescByTitle } from "./Features";
import BarChart from "./BarChart";
import PieChart from "./PieChart";


const Home = () => {

    const [elementList, setElementList] = useState(dummyElementList as IElement[])

    const [shownPage, setShownPage] = useState(PageEnum.list)
    const [datatoEdit, setDataToEdit] = useState({id:"", title:"", desc:"", gravity:1} as unknown as IElement);
    const [selectedSortOption, setSelectedSortOption] = useState("");
    const [chartjs, setChartjs] = useState();
    const [recordsPerPage, setRecordsPerPage] = useState(5);

    const [barchartData, setBarchartData] = useState<{ [gravity: number]: number }>({});

    const [isLoggedIn, setIsLoggedIn] = useState<boolean>(true);

    useEffect(() => {
        const checkLoginStatus = async () => {
            try {
//                 fetch('http://localhost:5000/api/users/login', {
//                 method: 'POST', // Specify the request method
//                 headers: {
//                 'Content-Type': 'application/json',
//                 },
//                 body: JSON.stringify({
//                     username: 'cristi',
//                     password: 'pwd',
//          }), 
// })
// .then(response => response.json())
// .then(data => console.log('Success:', data))
// .catch(error => console.error('Error:', error));
                // try to GET /api/users; if it returns 200, the user is logged in
                const response = await fetch('http://localhost:5000/api/users', { method: 'GET', 
                headers: {
                    'Content-Type': 'application/json',
                  }
                 }).then((res) => res.json());
                if (response.status === 403) {
                    setIsLoggedIn(false);
                }
                else {
                    setIsLoggedIn(true);
                    console.log('Not logged in');
                }
            } catch (error) {
                console.error('Error checking login status:', error);
                // Handle error (e.g., show error message)
            }
        };

        checkLoginStatus();
    }, []);

    const [currentPage, setCurrentPage] = useState(1);
    const totalPages = Math.ceil(elementList.length / recordsPerPage);
    const indexOfLastRecord = currentPage * recordsPerPage;
    const indexOfFirstRecord = indexOfLastRecord - recordsPerPage;
    const currentRecords = elementList.slice(indexOfFirstRecord, indexOfLastRecord);


   

    const addElementServer = async (data: IElement) => {
        try{
            const response = await fetch("/api/elements", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify(data),
            });
            if(response.ok){
                const data = await response.json();
                loadElementList();
                showListPage();
                return data;
            }
            loadElementList();
            showListPage();
        }catch(error){
            console.error(error);
        }
    }

    const updateElementServer = async (data: IElement) => {
        try{
            const response = await fetch(`/api/elements/${data.id}`, {
                method: "PATCH",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify(data),
            });
            if(response.ok){
                const data = await response.json();
                console.log(data);
            }
            loadElementList();
            showListPage();
        }catch(error){
            console.error(error);
        }

    };


    useEffect(() => {
        getChartData();
    }, []);
    const getChartData = async () => {
        try{
            const response = await fetch('http://localhost:5000/api/elements/chartdata');
            const data = await response.json();
            setBarchartData(data);
            return data;
        }catch(error){
            console.error(error);
        }
    }


    const onPaginationClick = async (page: number) => {
        
        try{
            const response = await fetch('api/elements/page?page=2&records=1');
            const data = (await response.json()).currentRecords;
            console.log(data);


            data.forEach((el: any) => {
                el.id = el._id;
            });
            setElementList(data);
            setCurrentPage(page);
            onPageChange(page);
        }
        catch(error){
            console.error(error);
        }
    };


    const loadElementList = async () => {
        try{
            const response = await fetch("/api/elements");
            const data = await response.json();
            // data has a field called `_id`
            // we need to convert it to `id`
            data.forEach((el: any) => {
                el.id = el._id;
            });
            setElementList(data);
        }catch(error){
            console.error(error);
        }
    }

    const deleteElementServer = async (data: IElement) => {
        try{
            const response = await fetch(`/api/elements/${data.id}`, {
                method: "DELETE",
            });
            if(response.ok){
                const data = await response.json();
                return data;
            }
            loadElementList();
        }catch(error){
            console.error(error);
        }
    }


    const onAddElementClickHandler = () => {
        setShownPage(PageEnum.add);
    }

    const showListPage = () => {
        setShownPage(PageEnum.list);
    }

    const addE = (data: IElement) => {
        setElementList([...elementList, data]);
        showListPage();
    }

    const deleteElement = (data: IElement) => {
        setElementList(elementList.filter((el) => el.id !== data.id));
    }

    const editElementData = (data: IElement) => {
        setShownPage(PageEnum.edit);
        setDataToEdit(data);
    }

    const updateData = (data: IElement) => {
        const updatedData = elementList.map((el) => {
            if(el.id === data.id){
                return data;
            }
            return el;
        });
        setElementList(updatedData);
        showListPage();
    }

    const handleRecordsPerPageChange = (e:any) => {
        setRecordsPerPage(parseInt(e.target.value));
        setCurrentPage(1);
    };

    const handleSortOptionChanged = (e:any) => {
        const selectedOption = e.target.value;
        setSelectedSortOption(selectedOption);

        let sortedList : IElement[] = [];

        switch (selectedOption){
            case "alphabetically-decrease":
                sortedList = sortDescByTitle({elementList});
                break;
            case "alphabetically-increase":
                sortedList = sortAscByTitle({elementList});
                break;
            case "gravity-increase":
                sortedList = sortAscByGravity({elementList});
                break;
            case "gravity-decrease":
                sortedList = sortDescByGravity({elementList});
                break;
            default:
                sortedList = elementList;
                break;
        }
        setElementList(sortedList);
    }

    const onPageChange = (page: number) => {
        setCurrentPage(page);
    };

   
    return (
        <>
        
        <div>
            {isLoggedIn ?
            (
            <><article className="article-header">
                            <header>React CRUD</header>
                        </article><section className="section-content">
                                {shownPage === PageEnum.list && (
                                    <>
                                        <div
                                            style={{
                                                display: "flex",
                                                justifyContent: "space-between",
                                            }}
                                        >
                                            <input
                                                type="button"
                                                value="ADD ELEMENT"
                                                style={{
                                                    fontSize: "1rem",
                                                    border: "1px solid #ccc",
                                                    borderRadius: "5px",
                                                }}
                                                onClick={onAddElementClickHandler} />
                                            <select
                                                className="sort-options"
                                                id="sort-options"
                                                data-testid="sort-options"
                                                onChange={handleSortOptionChanged}
                                            >
                                                <option value="sort-by">Sort By</option>
                                                <option value="alphabetically-increase">Title ↑</option>
                                                <option value="alphabetically-decrease">Title ↓</option>
                                                <option value="gravity-increase">Gravity ↑</option>
                                                <option value="gravity-decrease">Gravity ↓</option>
                                            </select>
                                        </div>
                                        <select className="records-display-options" data-testid="records-per-page" value={recordsPerPage} onChange={handleRecordsPerPageChange}>
                                            <option value={5}>5 per page</option>
                                            <option value={10}>10 per page</option>
                                            <option value={20}>20 per page</option>
                                            <option value={currentRecords.length}>All</option>
                                        </select>
                                        <ElementList
                                            list={currentRecords}
                                            onDeleteClickHandle={deleteElementServer}
                                            onEdit={editElementData} />
                                    </>
                                )}
                                {shownPage === PageEnum.add && (
                                    <AddElement
                                        onBackButtonClickHandle={showListPage}
                                        onSubmitClickHandle={addElementServer} />
                                )}

                                {shownPage === PageEnum.edit && (
                                    <EditElement
                                        data={datatoEdit}
                                        onBackButtonClickHandle={showListPage}
                                        onUpdateClickHandle={updateElementServer} />
                                )}
                                <div
                                    className="pagination"
                                    style={{ display: "flex", justifyContent: "center" }}
                                >
                                    <button
                                        style={{
                                            fontSize: "1rem",
                                            padding: "0.5rem",
                                            margin: "0.5rem",
                                            border: "1px solid #ccc",
                                            borderRadius: "5px",
                                        }}
                                        onClick={() => onPageChange(currentPage - 1)}
                                        disabled={currentPage === 1}
                                    >
                                        {"<"}
                                    </button>
                                    <div className="page-numbers">
                                        {Array.from({ length: totalPages }, (_, i) => i + 1).map((page) => (
                                            <button
                                                style={{
                                                    fontSize: "1rem",
                                                    padding: "0.5rem",
                                                    margin: "0.5rem",
                                                    border: "1px solid #ccc",
                                                    borderRadius: "5px",
                                                }}
                                                key={page}
                                                onClick={() => onPaginationClick(page)}
                                                className={page === currentPage ? "active" : ""}
                                            >
                                                {page}
                                            </button>
                                        ))}
                                    </div>
                                    <button
                                        style={{
                                            fontSize: "1rem",
                                            padding: "0.5rem",
                                            margin: "0.5rem",
                                            border: "1px solid #ccc",
                                            borderRadius: "5px",
                                        }}
                                        onClick={() => onPageChange(currentPage + 1)}
                                        disabled={indexOfLastRecord >= elementList.length}
                                    >
                                        {">"}
                                    </button>
                                </div>
                                <div style={{ display: "flex", justifyContent: "center", minHeight: "500px" }}>
                                    <BarChart elements={elementList} />
                                    <PieChart data={currentRecords} />
                                </div>
                            </section></>
            ):(<div>Not logged in</div>)}
        </div>
        </>
    );
    }

export default Home;