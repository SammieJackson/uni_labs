

class Error(Exception):
    # """Base class for other exceptions"""
    pass


class BadArgumentTypeException(Error):
    # """Raised when the input variable is of unintended type"""
    pass


class BadArgumentDimensionsException(Error):
    # """Raised when the input vectors length are uncoordinated"""
    pass


class BadArgument(Error):
    # """Raised when the argument does not satisfy certain requirements"""
    pass


'''
class ValidationError(Exception):
    def __init__(self, message, errors):

        # Call the base class constructor with the parameters it needs
        super(ValidationError, self).__init__(message)

        # Now for your custom code...
        self.errors = errors
#'''


'''
class ValidationError(Exception):
    def __init__(self, message, errors):

        # Call the base class constructor with the parameters it needs
        super().__init__(message)

        # Now for your custom code...
        self.errors = errors
#'''

