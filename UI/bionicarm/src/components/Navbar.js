import React from 'react'
// import { CNavbar, CButton,CContainer,CForm,CFormInput, CNavbarBrand } from '@coreui/react'
import '@coreui/coreui/dist/css/coreui.min.css'
import { useState } from 'react'
import {
    CNavbar,
    CContainer,
    CNavbarBrand,
    CNavbarToggler,
    CCollapse,
    CNavbarNav,
    CNavItem,
    CNavLink,
    CDropdown,
    CDropdownToggle,
    CDropdownMenu,
    CDropdownItem,
    CDropdownDivider,
    CButton,
    CForm,
    CFormInput
  } from '@coreui/react';
  

export default function Navbar() {

const [visible, setVisible] = useState(false)
  return (
    <>

<CNavbar expand="lg" colorScheme="light" className="bg-dark">
      <CContainer fluid >
        <CNavbarBrand href="#" className='text-white'>Bionic Arm</CNavbarBrand>
        <CNavbarToggler
          aria-label="Toggle navigation"
          aria-expanded={visible}
          onClick={() => setVisible(!visible)}
        />
        <CCollapse className="navbar-collapse" visible={visible}>
          <CNavbarNav>
            <CNavItem>
              <CNavLink href="#" className='text-white' active>
                Home
              </CNavLink>
            </CNavItem>
            </CNavbarNav>
            {/* <CNavItem>
              <CNavLink href="#">Features</CNavLink>
            </CNavItem>
            <CNavItem>
              <CNavLink href="#">Pricing</CNavLink>
            </CNavItem>
            <CDropdown variant="nav-item" popper={false}>
              <CDropdownToggle>Dropdown link</CDropdownToggle>
              <CDropdownMenu>
                <CDropdownItem href="#">Action</CDropdownItem>
                <CDropdownItem href="#">Another action</CDropdownItem>
                <CDropdownDivider />
                <CDropdownItem href="#">Something else here</CDropdownItem>
              </CDropdownMenu>
            </CDropdown> */}
            <CNavbarNav className='ms-auto'>
            <CNavItem >
          
   
    <CForm className="d-flex right">
      <CFormInput type="search" className="me-2" placeholder="Search" />
      <CButton type="submit" color="success" variant="outline">
        Search
      </CButton>
    </CForm>

  </CNavItem>
          </CNavbarNav>
        </CCollapse>
      </CContainer>
    </CNavbar>


    
 </>
  )
}


