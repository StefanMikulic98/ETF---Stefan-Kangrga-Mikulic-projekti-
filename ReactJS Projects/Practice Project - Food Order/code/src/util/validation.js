export function isEmail(value) {
    return value.includes('@');
}

export function isStreet(value) {
    return /\d/.test(value);
}

export function isNotEmpty(value) {
    return value.trim() !== '';
}

export function hasMaxLength(value, maxLength) {
    return value.length <= maxLength;
}