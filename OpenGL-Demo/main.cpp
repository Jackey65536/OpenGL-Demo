#define MAIN_SPACE(name) namespace name { int main(int argc, char* argv[]); }

// Demo
namespace Demo {
    MAIN_SPACE(Anisotropic)
    MAIN_SPACE(Blending)
    MAIN_SPACE(First)
    MAIN_SPACE(Geotest)
    MAIN_SPACE(Modelview_projection)
    MAIN_SPACE(Move)
    MAIN_SPACE(Movebymatrix)
    MAIN_SPACE(Objects)
    MAIN_SPACE(Orthographic)
    MAIN_SPACE(Perspective)
    MAIN_SPACE(Primitives)
    MAIN_SPACE(Pyramid)
    MAIN_SPACE(Scissor)
    MAIN_SPACE(Smoother)
    MAIN_SPACE(Sphere1)
    MAIN_SPACE(Sphere2)
    MAIN_SPACE(Sphere3)
    MAIN_SPACE(Sphere4)
    MAIN_SPACE(Sphere5)
    MAIN_SPACE(Tunnel)
}

// Test
namespace Test {
    MAIN_SPACE(DoubleTest)
    MAIN_SPACE(QuadsTest)
    MAIN_SPACE(DemoTest)
}

// Chapter01
namespace Ch01 {
    MAIN_SPACE(Block)
}

// Chapter02
namespace Ch02 {
    MAIN_SPACE(Bounce)
    MAIN_SPACE(Glrect)
    MAIN_SPACE(Simple)
}

// Chapter03
namespace Ch03 {
    MAIN_SPACE(Lines)
    MAIN_SPACE(Linesw)
    MAIN_SPACE(Lstipple)
    MAIN_SPACE(Lstrips)
    MAIN_SPACE(Points)
    MAIN_SPACE(Pointsz)
    MAIN_SPACE(Pstipple)
    MAIN_SPACE(Scissor)
    MAIN_SPACE(Single)
    MAIN_SPACE(Star)
    MAIN_SPACE(Stencil)
    MAIN_SPACE(Triangle)
}

// Chapter04
namespace Ch04 {
    MAIN_SPACE(Atom)
    MAIN_SPACE(Atom2)
    MAIN_SPACE(Ortho)
    MAIN_SPACE(Perspect)
    MAIN_SPACE(Solar)
    MAIN_SPACE(SphereWorld)
    MAIN_SPACE(Transform)
    MAIN_SPACE(Transformgl)
}

// Chapter05
namespace Ch05 {
    MAIN_SPACE(Ambient)
    MAIN_SPACE(Ccube)
    MAIN_SPACE(Jet)
    MAIN_SPACE(Litjet)
    MAIN_SPACE(Shadow)
    MAIN_SPACE(Shinyjet)
    MAIN_SPACE(Sphereworld)
    MAIN_SPACE(Spot)
    MAIN_SPACE(Triangle)
}

// Chapter06
namespace Ch06 {
    MAIN_SPACE(ADSGouraud)
    MAIN_SPACE(ADSPhong)
    MAIN_SPACE(DiffuseLight)
    MAIN_SPACE(Dissolve)
    MAIN_SPACE(FlatShader)
    MAIN_SPACE(LitTexture)
    MAIN_SPACE(ProvokingVertex)
    MAIN_SPACE(ShadedTriangle)
    MAIN_SPACE(TexturedTriangle)
    MAIN_SPACE(ToonShader)
    MAIN_SPACE(Triangle)
}

int main(int argc, char* argv[])
{
    return Ch06::TexturedTriangle::main(argc, argv);
}
