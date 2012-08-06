/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  ROUTE Plugin
 * Author:   SaltyPaws
 *
 ***************************************************************************
 *   Copyright (C) 2012 by Brazil BrokeTail                                *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "routegui_impl.h"

CfgDlg::CfgDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : CfgDlgDef( parent, id, title, pos, size, style )
{
}

Dlg::Dlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DlgDef( parent, id, title, pos, size, style )
{
    this->Fit();
}

void Dlg::OnToggle( wxCommandEvent& event )
{

}

void Dlg::OnCalculate( wxCommandEvent& event )
{

}
void Dlg::OnConverttoDegree( wxCommandEvent& event )
{
    //Lat1
    wxString Lat1 = this->m_Lat1_d->GetValue() + _T(" ")  + this->m_Lat1_m->GetValue() + _T(" ")  + this->m_Lat1_s->GetValue() + _T(" ");// + this->m_Lon1_EW->GetCurrentSelection();
    if(this->m_Lat1_NS->GetCurrentSelection()) //S=1
        Lat1=Lat1 + _T("S");
    else
        Lat1=Lat1 + _T("N");
    m_Lat1->SetValue(wxString::Format(wxT("%g"), fromDMStodouble((char*)Lat1.mb_str().data())));

    //Lon1
    wxString Lon1 = this->m_Lon1_d->GetValue() + _T(" ") + this->m_Lon1_m->GetValue() + _T(" ")  + this->m_Lon1_s->GetValue() + _T(" ") ;// + this->m_Lon1_EW->GetString();
    if(this->m_Lon1_EW->GetCurrentSelection()) //W=1
        Lon1=Lon1 + _T("W");
    else
        Lon1=Lon1 + _T("E");
    m_Lon1->SetValue(wxString::Format(wxT("%g"), fromDMStodouble((char*)Lon1.mb_str().data())));

    //Lat2
    wxString Lat2 = this->m_Lat2_d->GetValue() + _T(" ")  + this->m_Lat2_m->GetValue() + _T(" ")  + this->m_Lat2_s->GetValue() + _T(" ");//  + this->m_Lat2_NS->GetString();
    if(this->m_Lat2_NS->GetCurrentSelection()) //S=1
        Lat2=Lat2 + _T("S");
    else
        Lat2=Lat2 + _T("N");
    m_Lat2->SetValue(wxString::Format(wxT("%g"), fromDMStodouble((char*)Lat2.mb_str().data())));

    //Lon2
    wxString Lon2 = this->m_Lon2_d->GetValue() + _T(" ")  + this->m_Lon2_m->GetValue() + _T(" ")  + this->m_Lon2_s->GetValue() + _T(" ") ;// + _T(this->m_Lon2_EW->GetSelection());
    if(this->m_Lon2_EW->GetCurrentSelection()) //W=1
        Lon2=Lon2 + _T("W");
    else
        Lon2=Lon2 + _T("E");
    m_Lon2->SetValue(wxString::Format(wxT("%g"), fromDMStodouble((char*)Lon2.mb_str().data())));

}

void Dlg::OnNoteBookFit( wxCommandEvent& event )
{

        this->m_panel11->Layout();
    /*this->m_panel11->Fit();
    this->m_wxNotebook234->Layout();
    this->m_wxNotebook234->Fit();*/
    this->m_wxNotebook234->InvalidateBestSize();


    //this->Layout();
    this->Fit();
        printf("Resizing window \n");
}

void Dlg::OnGCCalculate( wxCommandEvent& event ){


    bool error_occured=false;
    double dist, fwdAz, revAz;

    double lat1,lon1,lat2,lon2;
    if(!this->m_Lat1->GetValue().ToDouble(&lat1)){ error_occured=true;}
    if(!this->m_Lon1->GetValue().ToDouble(&lon1)){ error_occured=true; }
    if(!this->m_Lat2->GetValue().ToDouble(&lat2)){ error_occured=true;}
    if(!this->m_Lon2->GetValue().ToDouble(&lon2)){ error_occured=true; }

    //Validate input ranges
    if (std::abs(lat1)>90){ error_occured=true; }
    if (std::abs(lat2)>90){ error_occured=true; }
    if (std::abs(lon1)>180){ error_occured=true; }
    if (std::abs(lon2)>180){ error_occured=true; }

    if(!DistVincenty(lat1, lon1, lat2, lon2, &dist, &fwdAz, &revAz)){ error_occured=true; };
    this->m_distance_GC->SetValue(wxString::Format(wxT("%g"), dist));

    DistanceBearingMercator(lat1, lon1, lat2, lon2, &fwdAz, &dist);
    this->m_distance_RH->SetValue(wxString::Format(wxT("%g"), dist));

    if (error_occured==true)  {
        wxLogMessage(_("Error in calculation. Please check input!") );
        wxMessageBox(_("Error in calculation. Please check input!") );}


}

void Dlg::OnFit( wxCommandEvent& event )
{

     //   this->m_panel11->Layout();
    /*this->m_panel11->Fit();
    this->m_wxNotebook234->Layout();
    this->m_wxNotebook234->Fit();*/
    this->m_wxNotebook234->InvalidateBestSize();
    this->m_panel11->Fit();
        this->m_panel11->Layout();

    //this->Layout();
    this->Fit();
    this->Layout();
    printf("Resizing window \n");
        //  wxMessageBox(_("User entered text:\n") );
}

void Dlg::OnExportGC( wxCommandEvent& event )
{
    //printf("You should see a file dialiog \n");

      wxFileDialog dlg(this, _("Export GPX file as"), wxEmptyString, wxEmptyString, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
      dlg.ShowModal();
      if (dlg.GetPath() != wxEmptyString){
            //wxMessageBox(_("User entered text:"), dlg.GetPath());


            bool error_occured=false;
            double dist, fwdAz, revAz;

            double lat1,lon1,lat2,lon2;
            if(!this->m_Lat1->GetValue().ToDouble(&lat1)){ error_occured=true;}
            if(!this->m_Lon1->GetValue().ToDouble(&lon1)){ error_occured=true; }
            if(!this->m_Lat2->GetValue().ToDouble(&lat2)){ error_occured=true;}
            if(!this->m_Lon2->GetValue().ToDouble(&lon2)){ error_occured=true; }

            //Validate input ranges
            if (std::abs(lat1)>90){ error_occured=true; }
            if (std::abs(lat2)>90){ error_occured=true; }
            if (std::abs(lon1)>180){ error_occured=true; }
            if (std::abs(lon2)>180){ error_occured=true; }

            if(!DistVincenty(lat1, lon1, lat2, lon2, &dist, &fwdAz, &revAz)){ error_occured=true; };
            this->m_distance_GC->SetValue(wxString::Format(wxT("%g"), dist));

           /* DistanceBearingMercator(lat1, lon1, lat2, lon2, &fwdAz, &dist);
            this->m_distance_RH->SetValue(wxString::Format(wxT("%g"), dist));*/

            if (error_occured==true)  {
                wxLogMessage(_("Error in calculation. Please check input!") );
                wxMessageBox(_("Error in calculation. Please check input!") );}

            ////////////////////Start XML
            TiXmlDocument doc;
//            TiXmlElement* msg;
            TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
            doc.LinkEndChild( decl );

            TiXmlElement * root = new TiXmlElement( "gpx" );
            doc.LinkEndChild( root );

            root->SetAttribute("version", "1.1");
            root->SetAttribute("creator", "Route_pi by SaltyPaws");
            root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
            root->SetAttribute("xmlns:gpxx","http://www.garmin.com/xmlschemas/GpxExtensions/v3" );
            root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
            root->SetAttribute("xmlns:opencpn","http://www.opencpn.org");


            TiXmlElement * Route = new TiXmlElement( "rte" );

            TiXmlElement * RouteName = new TiXmlElement( "name" );
            TiXmlText * text4 = new TiXmlText( "Route01" );
            Route->LinkEndChild( RouteName );
            RouteName->LinkEndChild( text4 );


            //////////////////////Add Points HERE

            double step_size;
            if(!this->m_IntervalNM->GetValue().ToDouble(&step_size)){ error_occured=true;}
            if ((step_size>dist) || (step_size<dist*1/5000)){
                wxLogMessage(_("Route interval > Distance, 0 or negative") );
                wxMessageBox(_("Route interval > Distance, 0 or negative") );
                }
            else
                {

                //start
                Addpoint(Route,wxString::Format(wxT("%f"),lat1),wxString::Format(wxT("%f"),lon1),_T("Start"),_T("diamond"),_T("WPT"));
                double lati, loni;
                for(double in_distance=step_size;in_distance<dist;in_distance=in_distance+step_size)
                    {
                    DestVincenty( lat1,  lon1,  fwdAz,  in_distance, &lati, &loni, &revAz);
                    std::cout<<"Distance: "<<in_distance<<"lat: "<<lati<<" lon: "<<loni<< std::endl;
                    Addpoint(Route,wxString::Format(wxT("%f"),lati),wxString::Format(wxT("%f"),loni), wxString::Format(wxT("%d"),(int)in_distance) ,_T("diamond"),_T("WPT"));
                    }
                //Addpoint(Route,(double)10,(double)11,(wxString)_T("NAAM"),(wxString)_T("SYMBOL"),(wxString)_T("TYPE"));

                //end
                Addpoint(Route,wxString::Format(wxT("%f"),lat2),wxString::Format(wxT("%f"),lon2),_T("Finish"),_T("SYMBOL"),_T("WPT"));
                //////////////////////////Close XML

                root->LinkEndChild( Route );
                wxString s=dlg.GetPath();


                    if (wxFileExists(dlg.GetPath()))
                        std::cout<<"file exists: no action"<< std::endl;
                    else{
                        std::cout<<"File does not exist: add.gpx"<< std::endl;
                         s = s + _T(".gpx");
                    }


                wxCharBuffer buffer=s.ToUTF8();
               // foo( buffer.data() );  // data() returns const char *
    //bar( buffer.data(), strlen(buffer.data()) );  // in case you need the length of the data

                std::cout<< buffer.data()<<std::endl;
                doc.SaveFile( buffer.data() );
                }
        }
//TiXmlDocument doc;
}

//void Dlg::Addpoint(TiXmlElement* Route, double ptlat, double ptlon, wxString ptname, wxString ptsym, wxString pttype){
void Dlg::Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon, wxString ptname, wxString ptsym, wxString pttype){
//add point
	TiXmlElement * RoutePoint = new TiXmlElement( "rtept" );
    RoutePoint->SetAttribute("lat", ptlat.mb_str());
    RoutePoint->SetAttribute("lon", ptlon.mb_str());


    TiXmlElement * Name = new TiXmlElement( "name" );
    TiXmlText * text = new TiXmlText( ptname.mb_str() );
    RoutePoint->LinkEndChild( Name );
    Name->LinkEndChild( text );

    TiXmlElement * Symbol = new TiXmlElement( "sym" );
    TiXmlText * text1 = new TiXmlText( ptsym.mb_str() );
    RoutePoint->LinkEndChild( Symbol );
    Symbol->LinkEndChild( text1 );

    TiXmlElement * Type = new TiXmlElement( "type" );
    TiXmlText * text2 = new TiXmlText( pttype.mb_str() );
    RoutePoint->LinkEndChild( Type );
    Type->LinkEndChild( text2 );
    Route->LinkEndChild( RoutePoint );
//done adding point
}

void Dlg::OnGCLCalculate( wxCommandEvent& event ){
    OnGCLCalculate (event, false);
    }


void Dlg::OnGCLCalculate( wxCommandEvent& event, bool write_file ){


    bool error_occured=false;
    double dist, fwdAz, revAz;
    wxString s;
       if (write_file){
            wxFileDialog dlg(this, _("Export GPX file as"), wxEmptyString, wxEmptyString, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            dlg.ShowModal();
            s=dlg.GetPath();
          //  std::cout<<s<< std::endl;
        if (dlg.GetPath() == wxEmptyString){ error_occured=true; printf("Empty Path\n");}
    }

    double lat1,lon1,lat2,lon2,limit;
    if(!this->m_Lat1->GetValue().ToDouble(&lat1)){ error_occured=true;}
    if(!this->m_Lon1->GetValue().ToDouble(&lon1)){ error_occured=true; }
    if(!this->m_Lat2->GetValue().ToDouble(&lat2)){ error_occured=true;}
    if(!this->m_Lon2->GetValue().ToDouble(&lon2)){ error_occured=true; }
    if(!this->m_LatLimit->GetValue().ToDouble(&limit)){ error_occured=true; }
    if (error_occured) printf("error in conversion of input coordinates\n");
;
    //Validate input ranges
    if (std::abs(lat1)>90){ error_occured=true; }
    if (std::abs(lat2)>90){ error_occured=true; }
    if (std::abs(lon1)>180){ error_occured=true; }
    if (std::abs(lon2)>180){ error_occured=true; }
    if (error_occured) printf("error in input range validation\n");


    if ((lat1>0) && (lat1>std::abs(limit))){ //North
        error_occured=true;
        wxMessageBox(_("Start Latitude>Limit!") );
        }
    if ((lat1<0) && (std::abs(lat1)>std::abs(limit))){ //south
        error_occured=true;
        wxMessageBox(_("Start Latitude>Limit!") );
        }
    if ((lat2>0) && (lat2>std::abs(limit))){ //North
        error_occured=true;
        wxMessageBox(_("Start Latitude>Limit!") );
        }
    if ((lat2<0) && (std::abs(lat2)>std::abs(limit))){ //south
        error_occured=true;
        wxMessageBox(_("Start Latitude>Limit!") );
        }
    //Calculate RH dist
    DistanceBearingMercator(lat1, lon1, lat2, lon2, &fwdAz, &dist);
    this->m_distance_RH1->SetValue(wxString::Format(wxT("%g"), dist));

    //Calculate GC
    if(!DistVincenty(lat1, lon1, lat2, lon2, &dist, &fwdAz, &revAz)){ error_occured=true;    printf("error in DistVincenty\n"); };
    this->m_distance_GC1->SetValue(wxString::Format(wxT("%g"), dist));


        TiXmlDocument doc;
//        TiXmlElement* msg;
        TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
        doc.LinkEndChild( decl );

        TiXmlElement * root = new TiXmlElement( "gpx" );

        TiXmlElement * Route = new TiXmlElement( "rte" );

        TiXmlElement * RouteName = new TiXmlElement( "name" );
        TiXmlText * text4 = new TiXmlText( "Route01" );

    if (write_file){
        doc.LinkEndChild( root );

        root->SetAttribute("version", "1.1");
        root->SetAttribute("creator", "Route_pi by SaltyPaws");
        root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
        root->SetAttribute("xmlns:gpxx","http://www.garmin.com/xmlschemas/GpxExtensions/v3" );
        root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
        root->SetAttribute("xmlns:opencpn","http://www.opencpn.org");

        Route->LinkEndChild( RouteName );
        RouteName->LinkEndChild( text4 );
    }

    //Calculate GCL
    double step_size=dist/100;

            if ((step_size>dist) || (step_size<dist*1/5000)  ){
                wxLogMessage(_("Route interval > Distance, 0 or negative") );
                wxMessageBox(_("Route interval > Distance, 0 or negative") );
                error_occured=true;
                }

            if (error_occured){
                wxLogMessage(_("Error occured, aborting GCL calc!") );
                //wxMessageBox(_("Route interval > Distance, 0 or negative") );
                }
            else
                {

                //start
                double lati=0, loni=0,latold=lat1,lonold=lon1,segment_distance=0,fwdAz_dummy=0,revAz_dummy=0;
                double GCL_dist=0;
                bool Lat_limit_found=false;
                double Lat_int1=0, Lat_int2=999999, Lon_int1=0, Lon_int2=0;

                for(double in_distance=0;in_distance<(dist+Tol());in_distance=in_distance+step_size)
                    {
                    DestVincenty( lat1,  lon1,  fwdAz,  in_distance, &lati, &loni, &revAz);

                    if ((lati>0) && (lati>std::abs(limit))){ //North
                        if (!Lat_limit_found){
                            std::cout<<"First intersection point"<< std::endl;
                            std::cout<<"------------->"<<"lat: "<<lati<<" lon: "<<loni<< std::endl;
                            Lat_int1=lati;
                            Lon_int1=loni;
                            Lat_limit_found=true;
                            lati=limit;
                            std::cout<<"------>N"<< std::endl;
                        }

                    }
                    else if ((lati<0) && (std::abs(lati)>std::abs(limit))){ //south
                        if (!Lat_limit_found){
                            std::cout<<"First intersection point"<< std::endl;
                            std::cout<<"------------->"<<"lat: "<<lati<<" lon: "<<loni<< std::endl;
                            Lat_int1=lati;
                            Lon_int1=loni;
                            Lat_limit_found=true;
                            lati=-(std::abs(limit));
                            std::cout<<"------>S"<< std::endl;
                        }

                    }
                    else{
                        if(Lat_limit_found && (Lat_int2 >99999)){
                            std::cout<<"Second intersection point"<< std::endl;
                            std::cout<<"------------->"<<"lat: "<<lati<<" lon: "<<loni<< std::endl;
                            Lat_int2=lati;
                            Lon_int2=loni;
                        }
                    }
                    //nothing yet}

                    if(!DistVincenty(latold, lonold, lati, loni, &segment_distance, &fwdAz_dummy, &revAz_dummy)){ error_occured=true; printf("error in 2nd Vncenty\n"); };
                    if (write_file){ Addpoint(Route,wxString::Format(wxT("%f"),lati),wxString::Format(wxT("%f"),loni), wxString::Format(wxT("%d"),(int)in_distance) ,_T("diamond"),_T("WPT"));}
                        GCL_dist += segment_distance;
                        //std::cout<<"Distance: "<<GCL_dist<<"lat: "<<lati<<" lon: "<<loni<< std::endl;
                        latold=lati;
                        lonold=loni;
                    }

                    //if Lat_limit_found we will do a limited circle calc, otherwise revert to great circle FIXME
                    //first GC: (lat1 ,lat2, Lat_int1,x (>Lat_int1&&<Lat_int2) )
                    if (Lat_limit_found){
                        if (Lat_int1>0){
                            Lat_int1=std::abs(limit);
                            Lat_int2=std::abs(limit);
                        }
                        else if (Lat_int1<0){
                            Lat_int1=-std::abs(limit);
                            Lat_int2=-std::abs(limit);
                        }
                        else
                            error_occured=true; //intersecting limit cannot be 0


                        int target_az=0;
                        if (fwdAz>0 && fwdAz<90) target_az = 270;
                        else if (fwdAz>90 && fwdAz<180) target_az = 270;
                        else if (fwdAz>180 && fwdAz<270) target_az = 90;
                        else if (fwdAz>270 && fwdAz<360) target_az = 90;
                        else {error_occured=1; std::cout<<"impossible course for GC!!! "<<fwdAz<<std::endl;}

                        //Find position of first section

                        this->lat1=lat1;
                        this->lon1=lon1;
                        this->lat2=Lat_int1;
                        //this->lon2=20;
                        this->targetAz=target_az;
                        {
                            double low_Limit = lon2 > lon1 ? lon1 : lon2;
                            double high_Limit = lon2 > lon1 ? lon2 : lon1;
                            double difference=high_Limit-low_Limit;
                            if (difference>180){
                                double tmp=high_Limit;
                                high_Limit=low_Limit+360;
                                low_Limit=tmp;
                                }

                            Lon_int1=BrentsMethodSolve(low_Limit,high_Limit,1e-13);
                            if (Lon_int1>180)
                                Lon_int1=Lon_int1-360;
                        }


                        //Second section
                        if (target_az==90)
                            target_az=270;
                        else if (target_az==270)
                            target_az=90;
                        else
                            error_occured=true;

                        this->lat1=lat2;
                        this->lon1=lon2;
                        this->lat2=Lat_int2;
                        //this->lon2=20;
                        this->targetAz=target_az;
                       {
                            double low_Limit = lon2 > lon1 ? lon1 : lon2;
                            double high_Limit = lon2 > lon1 ? lon2 : lon1;
                            double difference=high_Limit-low_Limit;
                            if (difference>180){
                                double tmp=high_Limit;
                                high_Limit=low_Limit+360;
                                low_Limit=tmp;
                                }
                            Lon_int2=BrentsMethodSolve(low_Limit,high_Limit,1e-13);
                            if (Lon_int2>180)
                                Lon_int2=Lon_int2-360;
                        }
                DistVincenty(lat1, lon1, Lat_int1, Lon_int1, &segment_distance, &fwdAz_dummy, &revAz_dummy);
               double LC_distance=segment_distance;
               DistVincenty(Lat_int1, Lon_int1, Lat_int2, Lon_int2, &segment_distance, &fwdAz_dummy, &revAz_dummy);
               LC_distance+=segment_distance;
               DistVincenty(Lat_int2, Lon_int2, lat2, lon2, &segment_distance, &fwdAz_dummy, &revAz_dummy);
               LC_distance+=segment_distance;

               //Write out distance to dialog box
               this->m_distance_LC->SetValue(wxString::Format(wxT("%g"), LC_distance));

                   }
                   else{
                   //no intersection, do normal GC
                       this->m_distance_GC1->SetValue(wxString::Format(wxT("%g"), dist));
                   this->m_distance_LC->SetValue(this->m_distance_GC1->GetValue());
                   }

               // Now we have found intersection, calculate length:



                if (write_file){
                    root->LinkEndChild( Route );
                    //wxString s=dlg.GetPath().c_str();
                   //std::cout<< s.c_str()<<std::endl;
                    // check if string ends with .gpx or .GPX
                    if (wxFileExists(s))
                        std::cout<<"file exists: no action"<< std::endl;
                    else{
                        std::cout<<"File does not exist: add.gpx"<< std::endl;
                         s = s + _T(".gpx");
                    }


                    wxCharBuffer buffer=s.ToUTF8();

                    std::cout<< buffer.data()<<std::endl;
                    doc.SaveFile( buffer.data() );}
                }

    if (error_occured==true)  {
        wxLogMessage(_("Error in calculation. Please check input!") );
        wxMessageBox(_("Error in calculation. Please check input!") );}

}

void Dlg::OnExportGCL( wxCommandEvent& event ){

    OnGCLCalculate (event, true);
}

double Dlg::F(double lonx)
{
   //return cos(x) - x*x*x;
   //std::cout<<"lat1 "<<lat1<<" lon1: " <<lon1<<"lat2 "<<lat2<<" lonx: " <<lonx<<" targetaz: "<<targetAz<< std::endl;
   double segment_distance_dummy, fwdAz_dummy, revAz_dummy;
   DistVincenty(lat1, lon1, lat2, lonx, &segment_distance_dummy, &fwdAz_dummy, &revAz_dummy);
   return revAz_dummy-targetAz;
}

double Dlg::BrentsMethodSolve(double lowerLimit, double upperLimit, double errorTol)
{
    std::cout<<"-------------------------------------------------------------"<< std::endl;
    double a = lowerLimit;
    double b = upperLimit;

    std::cout<<"lowerLimit: "<<lowerLimit<<" upperLimit: "<< upperLimit<< std::endl;
    double c = 0;
    double d = 0;

    double fa = F(a);
    double fb = F(b);
    std::cout<<"fa: "<<fa<<" fb: " <<fb<< std::endl;

    double fc = 0;
    double s = 0;
    double fs = 0;

    // if f(a) f(b) >= 0 then error-exit
    if (fa * fb >= 0)
    {
        if (fa < fb)
            return a;
        else
            return b;
    }

    // if |f(a)| < |f(b)| then swap (a,b) end if
    if (fabs(fa) < fabs(fb))
    { double tmp = a; a = b; b = tmp; tmp = fa; fa = fb; fb = tmp; }

    c = a;
    fc = fa;
    bool mflag = true;
    int i = 0;

    while (!(fb==0) && (fabs(a-b) > errorTol)&&(i<50))
    {
        if ((fa != fc) && (fb != fc))
            // Inverse quadratic interpolation
            s = a * fb * fc / (fa - fb) / (fa - fc) + b * fa * fc / (fb - fa) / (fb - fc) + c * fa * fb / (fc - fa) / (fc - fb);
        else
            // Secant Rule
            s = b - fb * (b - a) / (fb - fa);

        double tmp2 = (3 * a + b) / 4;
        if ((!(((s > tmp2) && (s < b)) || ((s < tmp2) && (s > b)))) || (mflag && (fabs(s - b) >= (fabs(b - c) / 2))) || (!mflag && (fabs(s - b) >= (fabs(c - d) / 2))))
        {
            s = (a + b) / 2;
            mflag = true;
        }
        else
        {
            if ((mflag && (fabs(b - c) < errorTol)) || (!mflag && (fabs(c - d) < errorTol)))
            {
                s = (a + b) / 2;
                mflag = true;
            }
            else
                mflag = false;
        }
        fs = F(s);
        d = c;
        c = b;
        fc = fb;
        if (fa * fs < 0) { b = s; fb = fs; }
        else { a = s; fa = fs; }

        // if |f(a)| < |f(b)| then swap (a,b) end if
        if (fabs(fa) < fabs(fb))
        { double tmp = a; a = b; b = tmp; tmp = fa; fa = fb; fb = tmp; }

        std::cout<<"Iteration: "<<i<<" lon: " <<b<<" target: "<<fs<< std::endl;
        i++;

//FIXME: check convergence or cry foul! (fs<tol())
    }
    if (i > 999)
    wxMessageBox(_("Brent's method not converging") );
    return b;
}

