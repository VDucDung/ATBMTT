//! 5 - Hàm mã hóa và giải mã theo thuật toán Caesar

// Ma hoa: Ek (i) = (i + k) mod N
// Ma hoa: Dk (i) = (i - k) mod N

const ALPHABET = 'abcdefghijklmnopqrstuvwxyz'

const N = ALPHABET.length

const maHoa = (plaintext = '', key) => {
  if (typeof key !== 'number') {
    alert('Tham số đầu không hợp lệ')
    return
    // throw new Error('Tham số đầu vào không hợp lệ')
  }

  plaintext = plaintext.trim().toLowerCase()
  let ciphertext = ''

  for (let i = 0; i < plaintext.length; i++) {
    const index = ALPHABET.indexOf(plaintext[i])
    if (index === -1) {
      ciphertext += plaintext[i]
    } else {
      const newIndex = (index + key) % N
      ciphertext += ALPHABET[newIndex]
    }
  }

  return ciphertext
}

const giaMa = (ciphertext = '', key) => {
  if (typeof key !== 'number') {
    alert('Tham số đầu không hợp lệ')
    return
  }

  ciphertext = ciphertext.trim().toLowerCase()

  let plaintext = ''

  for (let i = 0; i < ciphertext.length; i++) {
    const index = ALPHABET.indexOf(ciphertext[i])
    if (index === -1) {
      plaintext += ciphertext[i]
    } else {
      const newIndex = (index - key) % N
      plaintext += ALPHABET[newIndex]
    }
  }

  return plaintext
}
document.getElementById('encrypt').addEventListener('click', () => {
  const key = Number(document.getElementById('key').value)
  const input = document.getElementById('input').value
  document.getElementById('output').value = maHoa(input, key)
})

document.getElementById('decrypt').addEventListener('click', () => {
  const key = Number(document.getElementById('key').value)
  const input = document.getElementById('output').value
  document.getElementById('output').value = giaMa(input, key)
})
