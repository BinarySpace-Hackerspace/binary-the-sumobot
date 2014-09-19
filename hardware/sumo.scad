// from http://www.thingiverse.com/thing:18139
include<arduino.scad>



projection( cut = true )
{


// dozerMount
translate( [-42, 0, 0] ) dozerMount();
// motorMount
translate( [0, 0, 0] ) motorMount();
translate( [0, 37, 0] ) motorMount();
// bottom base
translate( [90, 0, 0] ) bottomBase();

// top base - export as dxf for lasercut
translate( [205, 0, 0] ) topBase();
}



/*
// dozer - export as stl for 3d printing
dozerComplete();
*/

module dozerComplete()
{
	sonarHoleSize = 17;
	difference()
	{
		dozer();
		translate( [-67, 35, -20] ) rotate( [0, 0, -45] ) cube( [60, 120, 60] , center = true);
		translate( [67, 35, -20] ) rotate( [0, 0, 45] ) cube( [60, 120, 60], center = true );

		translate( [-12.5, 32, -10] )
		{
			cylinder( r = sonarHoleSize/2, h = 10 );
			translate( [25, 0, 0] ) cylinder( r = sonarHoleSize/2, h = 10 );
		}
		translate( [-25, 44, -20] ) cube( [50, 10, 40] );
	}
}

module dozer()
{


	rotate( [ 270, 0, 0] )
	{
		difference()
		{
			translate( [0, 0, 10] )cube( [ 130, 22, 80], center = true );
			translate( [0, 12, 0] ) cube( [ 130, 10, 120], center = true );


			for ( i = [0 : 20] )
			translate( [ -2, -18, -16 + (3 * i )] ) 
			{
				rotate( [ 0, 90, 0] ) cylinder( r = 20, h = 136, center = true, $fn = 64 );
			}

			translate( [-20, 15, -12] )
			{
				rotate( [0, 0, 90] )
				{
					translate( [0, 0, 23] ) 
					rotate( [90, 180, 90] )
					{

						translate( [0, 3, -30] )
						{
							translate( [6, 2.5, -2] ) cylinder( r = 2, h = 50, $fn = 64 );
							translate( [6, 2.5 + 18, -2] ) cylinder( r = 2, h = 50, $fn = 64 );
							translate( [34, 2.5, -2] ) cylinder( r = 2, h = 50, $fn = 64 );
							translate( [34, 2.5 + 18, -2] ) cylinder( r = 2, h = 50, $fn = 64 );
						}
					}
				}
			}
		}

	}
}


// from http://www.thingiverse.com/thing:9347
module roundedRect(size, radius)
{
	x = size[0];
	y = size[1];
	z = size[2];

	linear_extrude(height=z)
	
	hull()
	{
		// place 4 circles in the corners, with the given radius
		translate([(-x/2)+(radius/2), (-y/2)+(radius/2), 0])
		circle(r=radius);

		translate([(x/2)-(radius/2), (-y/2)+(radius/2), 0])
		circle(r=radius);

		translate([(-x/2)+(radius/2), (y/2)-(radius/2), 0])
		circle(r=radius);

		translate([(x/2)-(radius/2), (y/2)-(radius/2), 0])
		circle(r=radius);
	}
}


module bottomBase()
{
	difference()
	{
	union()
	{
		translate( [0, 15,0]) roundedRect( [90, 115, 3], 5 );

		// line follow sensors
		translate( [0, -30,0]) roundedRect( [120, 20, 3], 5 );
	}

	// spacer holes
	translate( [ 42, 70, -4] ) spacer();
	translate( [ -42, 70, -4] ) spacer();
	translate( [ 42, -40, -4] ) spacer();
	translate( [ -42, -40, -4] ) spacer();

	mounts();

	//line follow sensors mount
	translate( [-57, -27, -4] ) 
	{
		cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [0, -8, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [8, -4, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
	}

	translate( [57, -27, -4] ) 
	{
		cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [0, -8, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [-8, -4, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
	}

	translate( [35, 70, -4] ) 
	{
		cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [-8, 0, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [-4, -6, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
	}

	translate( [-27, 70, -4] ) 
	{
		cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [-8, 0, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
		translate( [-4, -6, 0] ) cylinder( r = 2.5, h = 10, $fn = 64 );
	}

	}
}


module topBase()
{
	difference()
	{
		translate( [0, 15,0]) roundedRect( [90, 115, 3], 5 );

		// spacer holes
		translate( [ 42, 70, -4] ) spacer();
		translate( [ -42, 70, -4] ) spacer();
		translate( [ 42, -40, -4] ) spacer();
		translate( [ -42, -40, -4] ) spacer();

		mounts();

//		translate( [-40, 34, 0] ) cube( [80, 30, 50] );
		translate([20,-25, 8]) rotate( [0, 0, 180] ) Arduino(1, 1, 1);

	}
}

module mounts()
{
	translate( [-45, 50, 3.1] ) 
	{
		translate( [0, 0, 23] ) 
		rotate( [90, 180, 90] )
		motorMount();
	}

	translate( [42, 50, 3.1] )
	{ 
		translate( [0, 0, 23] ) 
		rotate( [90, 180, 90] )
		motorMount();
	}

	translate( [-20, -40, 3.1] )
	{
		rotate( [0, 0, 90] ) 
		{
			translate( [0, 0, 23] ) 
			rotate( [90, 180, 90] )
			dozerMount();
		}
	}
}

module spacer()
{
	cylinder( r = 2, h = 25, $fn = 64 );
}

module dozerMount()
{
	difference()
	{
		union()
		{
			translate( [0, -5, 0] ) cube( [ 40, 28, 3] );
			translate( [ 10, -8.5, 0]) cube( [ 20, 35, 3] );
		}

		translate( [0, -2, 0] )
		{
			translate( [4, 2.5, -2] ) cylinder( r = 1.5, h = 10, $fn = 64 );
			translate( [4, 2.5 + 18, -2] ) cylinder( r = 1.5, h = 10, $fn = 64 );
			translate( [36, 2.5, -2] ) cylinder( r = 1.5, h = 10, $fn = 64 );
			translate( [36, 2.5 + 18, -2] ) cylinder( r = 1.5, h = 10, $fn = 64 );
		}

		translate( [4, -1, -3] ) cube( [32, 3, 10] );
		translate( [4, 17, -3] ) cube( [32, 3, 10] );

	}
}

module motorMount()
{
	difference()
	{
		union()
		{
			translate( [0, -5, 0] ) cube( [ 40, 28, 3] );
			translate( [ 10, -8.5, 0]) cube( [ 20, 35, 3] );
		}

		translate( [5, 2.75, -2] ) cylinder( r = 1.4, h = 10, $fn = 64 );
		translate( [5, 2.25 + 18, -2] ) cylinder( r = 1.4, h = 10, $fn = 64 );
		translate( [ 25, 11.5, -3] ) cylinder( r = 6.7, h = 10, $fn = 64 );
	}
}