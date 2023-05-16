import React, { useState, useEffect } from 'react';
import axios from 'axios';
//import { CSSTransition } from 'react-transition-group';

const FileUploader = () => {
  const [selectedFile, setSelectedFile] = useState(null);
  const [response, setResponse] = useState(null);
  const [Class_name, setClass_name] = useState(null)

  const handleFileChange = (event) => {
    setSelectedFile(event.target.files[0]);
  };
  const handleResetClick = () => {
    window.location.reload(); // Refreshes the page
  };
 

  const handleSubmit = async (event) => {
    event.preventDefault();

    if (!selectedFile) {
      console.log('No file selected');
      return;
    }

    const formData = new FormData();
    formData.append('file', selectedFile);

    const headers = {
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
      }

    try {
      const response = await axios.post('http://127.0.0.1:8000/uploadcsv/', formData, {headers: headers});

      console.log(response.data["prediction class"]);
      setResponse(response.data["prediction class"]);
      
if (response === '1') {
    setClass_name('Scissors');
    } else {
    setClass_name('Paper');
    }
  
 
    } catch (error) {
      console.error(error);
    }
  };






return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
        justifyContent: "center",
        padding: "20px",
      }}
    >
        <h2 style = {{padding:"30px"}}>Enter the test data in CSV</h2>
      <form onSubmit={handleSubmit}>
        <input type="file" accept=".csv" onChange={handleFileChange} />
        <button type="submit">Upload</button>
      </form>
      {response && (
        // <div style={{padding:"20px"}}>
        //   <h3 >Prediction results</h3>
        
   

        //   <p className='text-center' style={{ color: 'red' }}>
        //   {response === '0' ? "Paper" : response === '1' ? "Scissors" : ""}
          
        //   </p>
        // <p>Hand motion in Progress</p>
        // <button className='btn' onClick={}>Reset</button>            
          
            
        // </div>

        <div
        style={{
          display: 'flex',
          justifyContent: 'center',
          border: '1px solid black', // Adds a boundary around the flex container
          padding: '10px',
          alignItems:'center',
          marginTop: '20px', // Adds a top margin of 20 pixels

        }}
        
      >
        <div>
          <h3>Prediction results</h3>

          <h1 className="text-center" style={{ color: 'red' }}>
            {response === '0' ? 'Paper' : response === '1' ? 'Scissors' : ''}
          </h1>

          <p className='text-center text-bold'>"Hand motion in Progress"</p>

        
        </div>
      </div>


      )}

{response && <button
            className="btn "
            style={{ backgroundColor: 'blue', color: 'white' ,alignContent:'center', marginTop:'10px'}} // Adds color to the button
            onClick={handleResetClick}
          >
            Reset
          </button>}
    </div>
  );
};

export default FileUploader;
