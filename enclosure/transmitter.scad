$fn = 100;
include <../../case-scad/case.scad>
include <../../case-scad/tripod-adapter.scad>


module transmitterPcb (size, offset) 
{   
    union () {
        pcb ([size.x, size.y, size.z], offset);
        
        // LED 5mm
        translate ([-50, 0, -3.1])
        rotate ([0, 90, 0])
        cylinder (20, d1=5.2, d2=5.2, center= true);

        // LED 3mm
        translate ([50, 6, -2.3])
        rotate ([0, 90, 0])
        cylinder (20, d1=3.2, d2=3.2, center= true);

        // USB
        translate ([50, -3.6, -2.3])
        cube ([20, 8.2, 3.2], center=true);

        // intensity
        translate ([-(size.x/2 -28.35), 17, -3.5])
        cube ([10+1, 10, 3 + 0.5], center=true);

        // on off
        translate ([27.81, 17, -5])
        cube ([8.7+1, 10, 3.8+0.5], center=true);
    }
}    
   
module icon (text, offset = 0, thick = 1) 
{
    //text("\u23FB");
    // scale([1, 1, 0.1])
    //surface(file = "power.png", center = true, invert = true);    
    minkowski () {
        cube ([17+offset, 17+ offset, thick / 2], center=true);
        cylinder (thick / 2, d1=3, d2=3, center=true);
    }
}

size = [100, 35, 30];
cutPercent = 27;

// Górna część. USZYTE.
union () {
    difference () {
        case (size, top = true, cutPercent=cutPercent);
        translate ([0, 0, 9.35]) 
        transmitterPcb ([size.x, size.y, 1], offset = -0.2);    
        
        // translate ([26, 5, 14.5])
        //icon ();

    //    translate ([-28, 5, 14.5])
    //    icon ();
    }
    
    // Dodatkowy wypust zamukający wyłacznik
    translate ([27.81, 17.05, 7])
    cube ([8.7+1, 0.9, 1], center=true);
}

// Dolna część obudowy. Wszystko uszyte do dziesiątych części mm.
difference () {
    case (size, top = false, cutPercent=cutPercent);

    translate ([0, 0, -17.5+3]) 
    glueConnect ([40, 25, 3], 0.1);
    
    // PCB
    translate ([0, 0, 9.35]) 
    transmitterPcb ([size.x, size.y, 1], offset = -0.2);    

    // Wycięcie dodatkowe na USB
    translate ([50, -3.6, -2.3+1.5+9.35])
    cube ([20, 8.2, 3.2+3], center=true);
    
    // Wycięcie dodatkowe na intensity
    translate ([-(size.x/2 -28.35), 17, -3.5 + 9.35 + 3])
    cube ([10+1, 10, 3 + 0.5 + 6], center=true);
    
    // Wycięcie dodatkowe na on off
    translate ([27.81, 17, -5+9.35+3])
    cube ([8.7+1, 10, 3.8+0.5+6], center=true); 
    
    // Wycięcie dodatkowe na LED 5mm
    translate ([-50, 0,  9.45])
    cube ([10, 5, 5], center = true);

    // Wycięcie dodatkowe na LED 3mm
    translate ([50, 6, 9.1])
    cube ([10, 3, 3], center = true);    
}

// Podstawka pod statuw   
union () {
    translate ([0, 0, -22.5]) {
        tripod ([40, 30]);
        translate ([0, 0, 2.5])
        glueConnect ([40, 30, 2], -0.2, cone=true);
    }
}

*translate ([0, 0, 9.35])
transmitterPcb ([size.x, size.y, 1], 0);

