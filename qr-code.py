import qrcode
from PIL import Image, ImageDraw

def qrGenerator(link,fileName="qrCode.png"):

    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=15,
        border=4,
    )

    qr.add_data(link)
    qr.make(fit=True)

    img = qr.make_image(fill_color="black",back_color="white")
    img.save(fileName)
    print(f"QR code saved as {fileName}")

qrGenerator("https://forms.gle/prWr2qk5EHPPtt4i6", "skillsharemarch-registration.png")