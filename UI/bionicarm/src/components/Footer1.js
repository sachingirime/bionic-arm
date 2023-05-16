import { CFooter, CLink } from '@coreui/react'

import React from 'react'

import { MDBFooter } from 'mdb-react-ui-kit';

export default function Footer() {

    
  return (

    <MDBFooter bgColor='' className='text-center  text-lg-left bg-dark '  style={{
        position: 'fixed',
        left: 0,
        bottom: 0,
        width: '100%',
        backgroundColor: 'rgba(0, 0, 0, 0.2)',
        padding: '1px',
        color: '#000',
        
      }}
    >
      <div className='text-center text-white p-3' style={{ backgroundColor: 'rgba(0, 0, 0, 0.2)' }}>
        &copy; {new Date().getFullYear()} Copyright:{' '}
        <a className='text-white' href=''>
          Team VEX
        </a>
      </div>
    </MDBFooter>
    
  )
}


