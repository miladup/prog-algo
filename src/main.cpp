#include <sil/sil.hpp>
#include "random.hpp"
#include <sstream>
#include <iomanip>
#include <cmath> // sin, cos, M_PI
#include <algorithm> // pour std::swap
#include <glm/glm.hpp>

void mettre_vert(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);
            pixel.r = 0; 
            pixel.b= 0;
        }
    }
}

#include <algorithm> // pour std::swap

void echanger_rouge_bleu(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);

            std::swap(pixel.r, pixel.b);
        }
    }
}

void noir_et_blanc(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);

            float gris = 0.299f * pixel.r +
                         0.587f * pixel.g +
                         0.114f * pixel.b;

            pixel.r = gris;
            pixel.g = gris;
            pixel.b = gris;
        }
    }
}

void negatif(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);

            // inversion des couleurs pour float 0..1
            pixel.r = 1.0f - pixel.r;
            pixel.g = 1.0f - pixel.g;
            pixel.b = 1.0f - pixel.b;
        }
    }
}

void creer_degrade_horizontal(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        float couleur = static_cast<float>(x) / (image.width() - 1);

        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);
            pixel.r = couleur;
            pixel.g = couleur;
            pixel.b = couleur;
        }
    }
}

void miroir_horizontal(const sil::Image& src, sil::Image& dst)
{
    for (int x = 0; x < src.width(); x++)
    {
        int xm = src.width() - 1 - x; // x miroir

        for (int y = 0; y < src.height(); y++)
        {
            dst.pixel(xm, y) = src.pixel(x, y);
        }
    }
}

void bruiter(sil::Image& image, float prob = 0.05f)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if (true_with_probability(prob))
            {
                auto& pixel = image.pixel(x, y);
                pixel.r = random_float(0.0f, 1.0f);
                pixel.g = random_float(0.0f, 1.0f);
                pixel.b = random_float(0.0f, 1.0f);
            }
        }
    }
}

void rotation_90_droite(const sil::Image& src, sil::Image& dst)
{
    // dst doit avoir taille height x width
    for (int x = 0; x < src.width(); x++)
    {
        for (int y = 0; y < src.height(); y++)
        {
            dst.pixel(src.height() - 1 - y, x) = src.pixel(x, y);
        }
    }
}

void rgb_split(const sil::Image& src, sil::Image& dst, int decalage)
{
    for (int x = 0; x < src.width(); x++)
    {
        for (int y = 0; y < src.height(); y++)
        {
            int xr = std::min(x + decalage, src.width() - 1);
            int xb = std::max(x - decalage, 0);

            const auto& pixel_r = src.pixel(xr, y);
            const auto& pixel_g = src.pixel(x, y);
            const auto& pixel_b = src.pixel(xb, y);

            auto& out = dst.pixel(x, y);
            out.r = pixel_r.r;
            out.g = pixel_g.g;
            out.b = pixel_b.b;
        }
    }
}

void creer_cercle(sil::Image& image)
{
    float cx = image.width() / 2.0f;
    float cy = image.height() / 2.0f;
    float rayon = 100.0f;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float dx = x - cx;
            float dy = y - cy;

            if (dx * dx + dy * dy <= rayon * rayon)
            {
                auto& pixel = image.pixel(x, y);
                pixel.r = 1.0f;
                pixel.g = 1.0f;
                pixel.b = 1.0f;
            }
        }
    }
}

// void creer_cercle_contour(sil::Image& image)
// {
//     float cx = image.width() / 2.0f;
//     float cy = image.height() / 2.0f;

//     float rayon = 100.0f;
//     float thickness = 5.0f; // épaisseur du contour

//     float r_ext2 = rayon * rayon;
//     float r_int2 = (rayon - thickness) * (rayon - thickness);

//     for (int x = 0; x < image.width(); x++)
//     {
//         for (int y = 0; y < image.height(); y++)
//         {
//             float dx = x - cx;
//             float dy = y - cy;
//             float d2 = dx * dx + dy * dy;

//             if (d2 >= r_int2 && d2 <= r_ext2)
//             {
//                 auto& pixel = image.pixel(x, y);
//                 pixel.r = 1.0f;
//                 pixel.g = 1.0f;
//                 pixel.b = 1.0f;
//             }
//         }
//     }
// }

void creer_cercle_contour(
    sil::Image& image,
    float cx, float cy,
    float rayon,
    float thickness)
{
    float r_ext2 = rayon * rayon;
    float r_int2 = (rayon - thickness) * (rayon - thickness);

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float dx = x - cx;
            float dy = y - cy;
            float d2 = dx * dx + dy * dy;

            if (d2 >= r_int2 && d2 <= r_ext2)
            {
                auto& pixel = image.pixel(x, y);
                pixel.r = 1.0f;
                pixel.g = 1.0f;
                pixel.b = 1.0f;
            }
        }
    }
}

void animer_cercle_gauche_droite()
{
    int width = 500;
    int height = 500;

    float cy = height / 2.0f;
    float rayon = 100.0f;

    int nb_frames = 60;

    for (int i = 0; i < nb_frames; i++)
    {
        sil::Image image{width, height}; // image noire

        float t = static_cast<float>(i) / (nb_frames - 1);
        float cx = rayon + t * (width - 2 * rayon);

        // dessin du disque
        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                float dx = x - cx;
                float dy = y - cy;

                if (dx * dx + dy * dy <= rayon * rayon)
                {
                    auto& pixel = image.pixel(x, y);
                    pixel.r = 1.0f;
                    pixel.g = 1.0f;
                    pixel.b = 1.0f;
                }
            }
        }

        std::ostringstream name;
        name << "output/frame_"
             << std::setw(3) << std::setfill('0')
             << i << ".png";

        image.save(name.str());
    }
}

#include <cmath>

void dessiner_rosace_6(sil::Image& image)
{
    float Cx = image.width() / 2.0f;
    float Cy = image.height() / 2.0f;

    float R = 100.0f; // rayon des cercles
    float thickness = 5.0f;

    // cercle central
    creer_cercle_contour(image, Cx, Cy, R, thickness);

    // 6 cercles autour
    for (int i = 0; i < 6; i++)
    {
        float angle = 2.0f * M_PI * i / 6.0f;

        float x = Cx + R * std::cos(angle);
        float y = Cy + R * std::sin(angle);

        creer_cercle_contour(image, x, y, R, thickness);
    }
}

void mosaique(const sil::Image& src, sil::Image& dst)
{
    for (int x = 0; x < dst.width(); x++)
    {
        for (int y = 0; y < dst.height(); y++)
        {
            int xs = x % src.width();
            int ys = y % src.height();

            dst.pixel(x, y) = src.pixel(xs, ys);
        }
    }
}

void mosaique_miroir(const sil::Image& src, sil::Image& dst)
{
    int w = src.width();
    int h = src.height();

    for (int x = 0; x < dst.width(); x++)
    {
        for (int y = 0; y < dst.height(); y++)
        {
            int tx = x / w; // indice colonne de tuile
            int ty = y / h; // indice ligne de tuile

            int xs = x % w;
            int ys = y % h;

            // une image sur deux inversée horizontalement
            if (tx % 2 == 1)
                xs = w - 1 - xs;

            // lignes 2, 4, etc → inversion verticale
            if (ty % 2 == 1)
                ys = h - 1 - ys;

            dst.pixel(x, y) = src.pixel(xs, ys);
        }
    }
}

void glitch(sil::Image& image, int nb_rectangles = 10, int rect_width = 50, int rect_height = 50)
{
    for (int i = 0; i < nb_rectangles; i++)
    {
        // Coordonnées du premier rectangle
        int x1 = random_int(0, image.width() - rect_width);
        int y1 = random_int(0, image.height() - rect_height);

        // Coordonnées du deuxième rectangle
        int x2 = random_int(0, image.width() - rect_width);
        int y2 = random_int(0, image.height() - rect_height);

        // On échange les pixels
        for (int dx = 0; dx < rect_width; dx++)
        {
            for (int dy = 0; dy < rect_height; dy++)
            {
                auto& p1 = image.pixel(x1 + dx, y1 + dy);
                auto& p2 = image.pixel(x2 + dx, y2 + dy);
                std::swap(p1, p2);
            }
        }
    }
}

void creer_degrade_couleur(sil::Image& image)
{
    glm::vec3 couleur_gauche(0.0f, 0.0f, 1.0f); // bleu
    glm::vec3 couleur_droite(1.0f, 0.0f, 0.0f); // rouge

    for (int x = 0; x < image.width(); x++)
    {
        float t = static_cast<float>(x) / (image.width() - 1);

        // mélange des deux couleurs
        glm::vec3 couleur = glm::mix(couleur_gauche, couleur_droite, t);

        for (int y = 0; y < image.height(); y++)
        {
            auto& pixel = image.pixel(x, y);
            pixel.r = couleur.r;
            pixel.g = couleur.g;
            pixel.b = couleur.b;
        }
    }
}

int main()
{
    // Mettre en vert
    {
        sil::Image image{"images/logo.png"};
        mettre_vert(image);
        image.save("output/pouet.png");
    }

    // Échanger rouge et bleu
    {
        sil::Image image{"images/logo.png"};
        echanger_rouge_bleu(image);
        image.save("output/logo_swap.png");
    }

    // Noir et blanc
    {
        sil::Image image{"images/logo.png"};
        noir_et_blanc(image);
        image.save("output/noir_blanc.png");
    }

    // Négatif
    {
        sil::Image image{"images/logo.png"};
        negatif(image);
        image.save("output/negatif.png");
    }

    // Dégradé horizontal (gris)
    {
        sil::Image degrade{256, 256};
        creer_degrade_horizontal(degrade);
        degrade.save("output/degrade.png");
    }

    // Miroir horizontal
    {
        sil::Image image{"images/logo.png"};
        sil::Image image_miroir{image.width(), image.height()};
        miroir_horizontal(image, image_miroir);
        image_miroir.save("output/logo_miroir.png");
    }

    // Ajouter du bruit
    {
        sil::Image image{"images/logo.png"};
        bruiter(image, 0.1f);
        image.save("output/logo_bruit.png");
    }

    // Rotation 90° droite
    {
        sil::Image image{"images/logo.png"};
        sil::Image image_rotate{image.height(), image.width()};
        rotation_90_droite(image, image_rotate);
        image_rotate.save("output/logo_90deg.png");
    }

    // Décalage RGB
    {
        sil::Image image{"images/logo.png"};
        sil::Image image_rgb{image.width(), image.height()};
        rgb_split(image, image_rgb, 30); // 30 pixels de décalage
        image_rgb.save("output/logo_rgb_split.png");
    }

    // Cercle plein
    {
        sil::Image image{500, 500};
        creer_cercle(image);
        image.save("output/cercle.png");
    }

    // Cercle contour
    {
        sil::Image image{500, 500};
        creer_cercle_contour(image, 250, 250, 100, 5); // centre (250,250), rayon 100, épaisseur 5
        image.save("output/cercle_contour.png");
    }

    // Animer cercle gauche → droite (génère 60 frames)
    {
        animer_cercle_gauche_droite();
    }

    // Rosace 6 cercles
    {
        sil::Image image{500, 500};
        dessiner_rosace_6(image);
        image.save("output/rosace_6.png");
    }

    // Mosaique simple
    {
        sil::Image image{"images/logo.png"};
        sil::Image mos{image.width() * 5, image.height() * 5};
        mosaique(image, mos);
        mos.save("output/mosaique.png");
    }

    // Mosaique miroir
    {
        sil::Image image{"images/logo.png"};
        sil::Image mos{image.width() * 5, image.height() * 5};
        mosaique_miroir(image, mos);
        mos.save("output/mosaique_miroir.png");
    }

    // Glitch
    {
        sil::Image image{"images/logo.png"};
        set_random_seed(42); // pour avoir le même résultat à chaque fois
        glitch(image, 30, 20, 5); // 30 rectangles de 20x5 pixels
        image.save("output/logo_glitch.png");
    }

    // Dégradé couleur (bleu → rouge)
    {
        sil::Image degrade_couleur{500, 500};
        creer_degrade_couleur(degrade_couleur);
        degrade_couleur.save("output/degrade_couleur.png");
    }
}