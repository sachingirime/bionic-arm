import React from 'react';
import Uploadfile from './components/Uploadfile';
//import ParticleBackground from 'react-particle-backgrounds'
import Navbar from './components/Navbar';
import Footer from './components/Footer1';



function App() {

  const settings = {
    canvas: {
      canvasFillSpace: true,
      width: 200,
      height: 200,
      useBouncyWalls: false
    },
    particle: {
      particleCount: 50,
      color: '#d68c38',
      minSize: 2,
      maxSize: 5
    },
    velocity: {
      directionAngle: 0,
      directionAngleVariance: 360,
      minSpeed: 1,
      maxSpeed: 3
    },
    opacity: {
      minOpacity: 0.2,
      maxOpacity: 0.6,
      opacityTransitionTime: 4000
    }
  }
  return (
    <div>
      <Navbar/>
   
      
      <Uploadfile/>

      <Footer />


  
    </div>
  );
}

export default App;
